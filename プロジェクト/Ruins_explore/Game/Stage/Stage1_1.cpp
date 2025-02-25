/*
	ファイル名：Stage1_1.cpp
	　　　概要：ステージ1_1を管理するクラス
*/
#include "pch.h"
#include "Stage1_1.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Stage1_1::Stage1_1(std::string stageName)
	:
	m_stageEnemy{},
	m_stageName{"Stage1_1"},
	m_stageObject{},
	m_isClearStage{},
	m_player{},
	m_sky{},
	m_timeUI{},
	m_gameTime{}
{
	// プレイヤーを作成する
	m_player = std::make_unique<Player>();
	// 敵を作成する
	m_stageEnemy = std::make_unique<StageEnemy>(m_player.get());
	// ステージのオブジェクトを作成する
	m_stageObject = std::make_unique<StageObject>(m_player.get());
	// ステージの装飾を作成する
	m_stageDecoration = std::make_unique<StageDecoration>();
	// 天球を作成
	m_sky = std::make_unique <Sky>();
	//TimeUIを作成
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
	);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Stage1_1::~Stage1_1()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Stage1_1::Initialize()
{
	// プレイヤーを初期化する
	m_player->Initialize();
	// 敵を初期化する
	m_stageEnemy->Initialize(m_stageName);
	// ステージのオブジェクトを初期化する
	m_stageObject->Initialize(m_stageName);
	// ステージの装飾を初期化する
	m_stageDecoration->Initialize(m_stageName);
	// 天球を初期化する
	m_sky->Initialize();
	// 時間UIを初期化する
	m_timeUI->Initialize();

	// ステージクリアフラグを初期化する
	m_isClearStage = false;
	// ゲーム時間を設定
	m_gameTime = MAX_GAMETIME;
	// 当たり判定クラスにプレイヤーを設定する
	Collision::GetInstance()->SetPlayer(m_player.get());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Stage1_1::Update(float elapsedTime)
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
	// ステージの装飾を更新する
	m_stageDecoration->Update();


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
void Stage1_1::Render()
{
	// 天球を描画
	m_sky->Render();
	// ステージのオブジェクトを描画する
	m_stageObject->Render();
	// ステージの装飾を描画する
	m_stageDecoration->Render();
	// 敵を描画する
	m_stageEnemy->Render();
	// プレイヤーを描画
	m_player->Render();
	//TextUIを描画
	m_timeUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Stage1_1::Finalize()
{
	m_player->Finalize();
	m_sky->Finalize();
	m_stageEnemy->Finalize();
	m_timeUI->Finalize();
}