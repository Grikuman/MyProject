/*
	@file	PlayerUIManagerUIManager.cpp
	@brief	プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "Game/UI/PlayerUIManager.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerUIManager::PlayerUIManager(Player* player)
	:
	m_player{player},
	m_playerHPUI{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerUIManager::~PlayerUIManager()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerUIManager::Initialize(CommonResources* resources)
{
	assert(resources);

	// プレイヤーのHPUIを作成する
	m_playerHPUI = std::make_unique<PlayerHPUI>(m_player);
	m_playerHPUI->Initialize(resources);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerUIManager::Update()
{
	// プレイヤーのHPUIを更新する
	m_playerHPUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerUIManager::Render()
{
	// プレイヤーのHPUIを描画する
	m_playerHPUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerUIManager::Finalize()
{
	m_playerHPUI->Finalize();
}