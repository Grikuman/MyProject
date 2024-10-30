/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"
#include <iostream>
#include "WorkTool/Collision.h"
#include "WorkTool/Data.h"
#include <wrl/client.h>
#include "ScreenGrab.h"
#include "wincodec.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_player{},
	m_sky{},
	m_field{},
	m_enemySpawner{},
	m_timeUI{},
	m_gameTime{}
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
	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	// プレイヤーを作成
	m_player = std::make_unique<Player>();
	m_player->Initialize();
	// 天球を作成
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize();
	// フィールドを作成
	m_field = std::make_unique<Field>();
	m_field->Initialize();
	// エネミースポナーを作成
	m_enemySpawner = std::make_unique<EnemySpawner>(m_player.get());
	m_enemySpawner->Initialize();
	//TextUIを作成
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
		);

	// ゲーム時間を設定
	m_gameTime = MAX_GAMETIME;

	// 当たり判定クラスにプレイヤーを設定する
	Collision::GetInstance()->SetPlayer(m_player.get());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	
	//ゲーム時間
	m_gameTime -= elapsedTime;

	//プレイヤーを更新
	m_player->Update(elapsedTime);
	// 天球を更新
	//m_sky->Update();
	// フィールドを更新
	m_field->Update();
	// エネミースポナーを更新
	m_enemySpawner->Update();
	// TextUIを更新
	m_timeUI->Update(m_gameTime);


	// 敵が全員死んだらシーン遷移を行う
	if (m_enemySpawner->IsChangeScene())
	{
		m_isChangeScene = true;
		// プレイ結果をClearにする
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	// プレイヤーの体力が0になったらシーン遷移を行う
	if (m_player->GetHP() <= 0)
	{
		m_isChangeScene = true;
		// プレイ結果をDeadにする
		Data::GetInstance()->SetPlaySceneResult(false);
	}

	//------------------------------------------------------------------
	// デバッグ機能
	//------------------------------------------------------------------
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();
	if (kb->IsKeyPressed(Keyboard::Q))
	{
		m_isChangeScene = true;
		// プレイ結果をClearにする
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	if (kb->IsKeyPressed(Keyboard::E))
	{
		m_isChangeScene = true;
		// プレイ結果をDeadにする
		Data::GetInstance()->SetPlaySceneResult(false);
	}
	//------------------------------------------------------------------

	// 次のシーンIDを取得する
	GetNextSceneID();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	// 天球を描画
	m_sky->Render();
	// フィールドを描画
	m_field->Render();
	// エネミースポナーを描画
	m_enemySpawner->Render();
	// プレイヤーを描画
	m_player->Render();
	//TextUIを描画
	m_timeUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	m_player->Finalize();
	m_sky->Finalize();
	m_field->Finalize();
	m_enemySpawner->Finalize();
	m_timeUI->Finalize();
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

void PlayScene::SaveScreenshotOnExit(IDXGISwapChain* swapChain, ID3D11DeviceContext* deviceContext)
{
	// スワップチェインのバックバッファを取得
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	// スクリーンショットを PNG ファイルに保存
	hr = DirectX::SaveWICTextureToFile(
		deviceContext,
		backBuffer.Get(),
		GUID_ContainerFormatPng,  // PNG形式で保存
		L"PlayScreen.png"  // ファイル名
	);
}
