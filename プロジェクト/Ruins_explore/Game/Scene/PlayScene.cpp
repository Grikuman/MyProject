/*
	ファイル名：PlayScene.cpp
	　　　概要：プレイシーンを管理するクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "Framework/Data.h"
#include "Framework/Audio.h"
#include "Framework/Graphics.h"
#include "Libraries/Microsoft/ReadData.h"
#include "Libraries/Microsoft/RenderTexture.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_currentStage{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayScene::Initialize()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	// 選択したステージ
	StageID selectStage = StageID::Stage1_2;
	// 選択したステージを生成する
	m_currentStage = StageFactory::CreateStage(selectStage);
	m_currentStage->Initialize();

	// レンダーテクスチャを作成する
	CreateRenderTexture(device);
	// ポストプロセスを作成する
	m_basicPostProcess = std::make_unique<DirectX::BasicPostProcess>(device);
	m_dualPostProcess = std::make_unique<DirectX::DualPostProcess>(device);

	// オーディオを再生
	Audio::GetInstance()->PlayBGM("PlayBGM",0.2f);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	m_currentStage->Update(elapsedTime);

	// ステージをクリアしたら次のステージへ進む
	if (m_currentStage->IsClearStage()) 
	{
		TransitionToNextStage();
	}

	// 次のシーンIDを取得する
	GetNextSceneID();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// オフスクリーンのRTVと既定の深度バッファを取得する
	auto offScreenRTV = m_offScreenRT->GetRenderTargetView();
	auto defaultDSV = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();

	// offScreenRTVをクリアする
	context->ClearRenderTargetView(offScreenRTV, DirectX::Colors::MidnightBlue);
	// 深度バッファをクリアする
	context->ClearDepthStencilView(defaultDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	// レンダーターゲットにoffScreenRTVとdefaultDSVを設定する
	context->OMSetRenderTargets(1, &offScreenRTV, defaultDSV);

	// ステージを描画する
	m_currentStage->Render();

	// ポストエフェクトで使用するRTVとSRVを取得する
	auto blur1RTV = m_blur1RT->GetRenderTargetView(); 
	auto blur1SRV = m_blur1RT->GetShaderResourceView(); 
	auto blur2RTV = m_blur2RT->GetRenderTargetView(); 
	auto blur2SRV = m_blur2RT->GetShaderResourceView(); 

	// オフスクリーンのSRVを取得する
	auto offScreenSRV = m_offScreenRT->GetShaderResourceView(); 

	// SRVクリア用の設定を準備する
	// DualPostProcessでは、２つのSRVを使用するので、配列の大きさも２つ分
	ID3D11ShaderResourceView* nullsrv[] = { nullptr,nullptr }; 

	// ビューポートをポストエフェクト用の小さいサイズに変更する
	// Pass1～Pass3まで使用する
	D3D11_VIEWPORT vp =
	{ 0.0f,0.0f,m_screenSize.right / 2.f,m_screenSize.bottom / 2.f,0.f,1.f };  
	context->RSSetViewports(1, &vp);

	// ポストプロセスの実行に深度バッファは必要ない
	context->OMSetRenderTargets(1, &blur1RTV, nullptr); 

	// ブルーム処理を実行する
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomExtract);
	m_basicPostProcess->SetBloomExtractParameter(0.25f); 
	m_basicPostProcess->SetSourceTexture(offScreenSRV);  
	m_basicPostProcess->Process(context); 

	// レンダーターゲットをblur2に変更する
	context->OMSetRenderTargets(1, &blur2RTV, nullptr);

	// 横ブラー処理を実行する
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters(true, 4.0f, 1.0f);
	m_basicPostProcess->SetSourceTexture(blur1SRV);
	m_basicPostProcess->Process(context);

	// SRVを1つ分クリアする
	context->PSSetShaderResources(0, 1, nullsrv);

	// レンダーターゲットをblur1に変更する
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	// 縦ブラー処理を実行する
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters(false, 2.0f, 1.0f); 
	m_basicPostProcess->SetSourceTexture(blur2SRV); 
	m_basicPostProcess->Process(context); 

	// レンダーターゲットをフレームバッファに変更する
	// 2D描画のため、深度ステンシルバッファは指定しなくてよい
	auto defaultRTV = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	context->OMSetRenderTargets(1, &defaultRTV, nullptr);

	// ビューポートは既定のものを指定する
	const auto& defaultVP = Graphics::GetInstance()->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &defaultVP);

	// オフスクリーン画像とブラー画像をポストプロセスのパラメータを加えてマージする
	m_dualPostProcess->SetEffect(DirectX::DualPostProcess::BloomCombine); 
	m_dualPostProcess->SetBloomCombineParameters(0.5f, 1.0f, 1.0f, 1.0f); 
	m_dualPostProcess->SetSourceTexture(offScreenSRV); 
	m_dualPostProcess->SetSourceTexture2(blur1SRV); 
	m_dualPostProcess->Process(context); 

	// SRVを２つ使っているので、２つ分をクリアする
	context->PSSetShaderResources(0, 2, nullsrv); 
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// ステージの終了処理
	m_currentStage->Finalize();
}

//---------------------------------------------------------
// 次のステージへの移行を処理する
//---------------------------------------------------------
void PlayScene::TransitionToNextStage()
{
	// 現在のステージの終了処理
	m_currentStage->Finalize();
	// 次のステージIDを取得
	StageID nextStageID = m_currentStage->GetNextStageID();

	// 次のステージを生成
	if (nextStageID != StageID::NONE)
	{
		m_currentStage = StageFactory::CreateStage(nextStageID);
		m_currentStage->Initialize();
	}
	else
	{
		// 全ステージ終了後、シーン変更フラグを設定
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// レンダーテクスチャを作成する
//---------------------------------------------------------
void PlayScene::CreateRenderTexture(ID3D11Device* device)
{
	// スクリーンサイズを取得する
	m_screenSize = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();

	// ブルームブラー用に画面の半分の大きさを計算する
	RECT halfSize{ 0,0,m_screenSize.right / 2,m_screenSize.bottom / 2 };

	// オフスクリーン用
	m_offScreenRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_offScreenRT->SetDevice(device);
	m_offScreenRT->SetWindow(m_screenSize);
	// ブルームブラー用
	m_blur1RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_blur1RT->SetDevice(device);
	m_blur1RT->SetWindow(halfSize);
	m_blur2RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_blur2RT->SetDevice(device);
	m_blur2RT->SetWindow(halfSize);
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}
