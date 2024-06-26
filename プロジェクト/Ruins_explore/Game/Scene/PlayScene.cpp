/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"
#include <iostream>
#include "Game/Stage/Sky.h"
#include "Game/Stage/Field.h"
#include "Game/Enemy/EnemySpawner.h"

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
	m_enemySpawner{}
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

	// プレイヤーを生成
	m_player = std::make_unique<Player>();
	m_player->Initialize(m_commonResources);
	// 天球を生成
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize(m_commonResources);
	// フィールドを生成
	m_field = std::make_unique<Field>();
	m_field->Initialize(m_commonResources);
	// Bodyからカメラを取得して設定する
	NRLib::TPS_Camera* playerCamera = m_player->GetCamera();
	if (playerCamera)
	{
		m_field->SetCamera(playerCamera);
	}
	// エネミースポナーを生成
	m_enemySpawner = std::make_unique<EnemySpawner>();
	m_enemySpawner->Initialize(m_commonResources,playerCamera);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//プレイヤーを更新
	m_player->Update(elapsedTime);
	
	m_sky->Update();
	m_field->Update();
	m_enemySpawner->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	//プレイヤーを描画
	m_player->Render();
	m_sky->Render();
	m_field->Render();
	m_enemySpawner->Render();
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
