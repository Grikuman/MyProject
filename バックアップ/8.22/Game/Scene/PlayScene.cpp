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

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_commonResources{},
	m_isChangeScene{},
	m_player{},
	m_sky{},
	m_field{},
	m_enemySpawner{},
	m_textUI{},
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
void PlayScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	// プレイヤーを作成
	m_player = std::make_unique<Player>();
	m_player->Initialize(m_commonResources);
	// 天球を作成
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize(m_commonResources);
	// フィールドを作成
	m_field = std::make_unique<Field>();
	m_field->Initialize(m_commonResources, m_player->GetCamera());
	// エネミースポナーを作成
	m_enemySpawner = std::make_unique<EnemySpawner>();
	m_enemySpawner->Initialize(m_commonResources, m_player->GetCamera());
	//TextUIを作成
	m_textUI = std::make_unique<TextUI>(
		m_commonResources->GetDeviceResources()->GetD3DDevice(),
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		);

	// ゲーム時間を設定
	m_gameTime = MAX_GAMETIME;
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
	m_sky->Update();
	// フィールドを更新
	m_field->Update();
	// エネミースポナーを更新
	m_enemySpawner->Update(m_player->GetBoundingSphere(), m_player->GetIsAttack());
	// TextUIを更新
	m_textUI->Update(m_gameTime);
	// 敵が全員死んだらシーン遷移を行う
	if (m_enemySpawner->IsChangeScene())
	{
		m_isChangeScene = true;
	}
	// 次のシーンIDを取得する
	GetNextSceneID();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	// プレイヤーを描画
	m_player->Render();
	// 天球を描画
	//m_sky->Render();
	// フィールドを描画
	m_field->Render();
	// エネミースポナーを描画
	m_enemySpawner->Render();
	//TextUIを描画
	m_textUI->Render();
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
	m_textUI->Finalize();
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
