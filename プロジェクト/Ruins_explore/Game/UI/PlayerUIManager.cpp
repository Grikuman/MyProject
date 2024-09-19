/*
	@file	PlayerUIManagerUIManager.cpp
	@brief	プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "Game/UI/PlayerUIManager.h"

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
	m_playerStatusUI{}
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
void PlayerUIManager::Initialize()
{
	// プレイヤーのHPUIを作成する
	m_playerStatusUI = std::make_unique<PlayerStatusUI>(m_player);
	m_playerStatusUI->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerUIManager::Update()
{
	// プレイヤーのHPUIを更新する
	m_playerStatusUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerUIManager::Render()
{
	// プレイヤーのHPUIを描画する
	m_playerStatusUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerUIManager::Finalize()
{
	m_playerStatusUI->Finalize();
}