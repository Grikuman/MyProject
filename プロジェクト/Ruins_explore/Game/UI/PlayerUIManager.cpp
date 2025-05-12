/*
	ファイル名：PlayerUIManager.cpp
	　　　概要：プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "Game/UI/PlayerUIManager.h"
#include "Game/Player/Player.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerUIManager::PlayerUIManager()
	:
	m_player{},
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
	// プレイヤーのポインタを取得する
	m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
	// プレイヤーのHPUIを作成する
	m_playerStatusUI = std::make_unique<PlayerStatusUI>();
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
// 終了処理
//---------------------------------------------------------
void PlayerUIManager::Finalize()
{
	m_playerStatusUI->Finalize();
}