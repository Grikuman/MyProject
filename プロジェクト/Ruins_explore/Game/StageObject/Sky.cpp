/*
	ファイル名：Sky.cpp
	　　　概要：空を表示するクラス
*/
#include "pch.h"
#include "Sky.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Sky::Sky()
	:
	m_projection{},
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Sky::~Sky()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Sky::Initialize()
{
	auto device  = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// 射影行列を作成する
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		1280 / 720,
		0.1f, 1000.0f
	);
	/*
		・射影行列のfarプレーンを遠くする
		・カメラのfarプレーンを状況に応じてイイ感じに調整する
		メモ:
		45.fはカメラの画角
		static_castを行っている部分は画面サイズ
		0.1fはカメラが見える一番近い距離
		1000.fの部分を100.fなどにすると映らなくなる場合がある
	*/


	// モデルを読み込む準備
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = Model::CreateFromCMO(device, L"Resources/Models/skydome_sky.cmo", *fx);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Sky::Update()
{
	
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Sky::Render()
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = Graphics::GetInstance()->GetCommonStates();

	// ビュー行列を取得する
	Matrix view = Graphics::GetInstance()->GetViewMatrix();


	// モデルのエフェクト情報を更新する
	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//// ライトを有効化する
				//basicEffect->SetLightingEnabled(true);
				/*
					・モデルクラスではデフォルトで内部的にライトが有効化されている
					・この設定が無くてもライトは有効化されている
				*/

				// 個別のライトをすべて無効化する
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// ワールド行列を更新する
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateRotationX(XMConvertToRadians(180));

	// モデルを描画する
	m_model->Draw(context, *states, world, view, m_projection);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Sky::Finalize()
{
	
}
