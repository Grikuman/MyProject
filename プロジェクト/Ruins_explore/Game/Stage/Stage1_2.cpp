/*
	ファイル名：Stage1_2.cpp
	　　　概要：ステージ1_2を管理するクラス
*/
#include "pch.h"
#include "Stage1_2.h"
#include "Framework/DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Framework/Graphics.h"
#include <iostream>
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include <wrl/client.h>
#include "ScreenGrab.h"
#include "wincodec.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Stage1_2::Stage1_2(std::string stageName)
	:
	m_stageEnemy{},
	m_stageName{"Stage1_2"},
	m_stageObject{},
	m_isClearStage{},
	m_player{},
	m_sky{},
	m_timeUI{},
	m_gameTime{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Stage1_2::~Stage1_2()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Stage1_2::Initialize()
{
	// ステージクリアフラグを初期化する
	m_isClearStage = false;

	// プレイヤーを作成
	m_player = std::make_unique<Player>();
	m_player->Initialize();
	// 敵を作成する
	m_stageEnemy = std::make_unique<StageEnemy>(m_player.get());
	m_stageEnemy->Initialize(m_stageName);
	// ステージのオブジェクトを作成する
	m_stageObject = std::make_unique<StageObject>(m_player.get());
	m_stageObject->Initialize(m_stageName);
	// 天球を作成
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize();
	//TimeUIを作成
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
		);
	// TimeUIを初期化する
	m_timeUI->Initialize();

	// ゲーム時間を設定
	m_gameTime = MAX_GAMETIME;

	// 当たり判定クラスにプレイヤーを設定する
	Collision::GetInstance()->SetPlayer(m_player.get());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Stage1_2::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	
	//ゲーム時間
	m_gameTime -= elapsedTime;

	//プレイヤーを更新
	m_player->Update(elapsedTime);
	// 敵を更新
	m_stageEnemy->Update();
	// 天球を更新
	m_sky->Update();
	// TextUIを更新
	m_timeUI->Update(m_gameTime);
	// ステージのオブジェクトを更新する
	m_stageObject->Update();


	// 敵が全員死んだらシーン遷移を行う
	if (m_stageEnemy->IsChangeStage())
	{
		m_isClearStage = true;
		// プレイ結果をClearにする
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	// プレイヤーの体力が0になったらシーン遷移を行う
	if (m_player->GetHP() <= 0)
	{
		m_isClearStage = true;
		// プレイ結果をDeadにする
		Data::GetInstance()->SetPlaySceneResult(false);
	}

	//------------------------------------------------------------------
	// デバッグ機能
	//------------------------------------------------------------------
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();
	if (kb->IsKeyPressed(DirectX::Keyboard::Q))
	{
		m_isClearStage = true;
		// プレイ結果をClearにする
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	if (kb->IsKeyPressed(DirectX::Keyboard::E))
	{
		m_isClearStage = true;
		// プレイ結果をDeadにする
		Data::GetInstance()->SetPlaySceneResult(false);
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Stage1_2::Render()
{
	// 天球を描画
	m_sky->Render();
	// 敵を描画する
	m_stageEnemy->Render();
	// ステージのオブジェクトを描画する
	m_stageObject->Render();
	// プレイヤーを描画
	m_player->Render();
	//TextUIを描画
	m_timeUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Stage1_2::Finalize()
{
	m_player->Finalize();
	m_sky->Finalize();
	m_stageEnemy->Finalize();
	m_timeUI->Finalize();
}