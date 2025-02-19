/*
    ファイル名：PlayerEffectManager.cpp
    　　　概要：プレイヤーのエフェクトクラスを管理するクラス
*/
#pragma once
#include "pch.h"
#include "Game/Effect/PlayerEffectManager.h"
#include "Game/Player/Player.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerEffectManager::PlayerEffectManager(Player* player)
    :
    m_player{player},
    m_invincibleEffect{}
{
    
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerEffectManager::~PlayerEffectManager()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerEffectManager::Initialize()
{
    // 無敵エフェクトを作成する
    m_invincibleEffect = std::make_unique<InvincibleEffect>(m_player);
    // 無敵エフェクトを初期化する
    m_invincibleEffect->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerEffectManager::Update()
{
    // 無敵エフェクトを更新する
    m_invincibleEffect->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerEffectManager::Render()
{
    // 無敵エフェクトを描画する
    m_invincibleEffect->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerEffectManager::Finalize()
{
    m_invincibleEffect->Finalize();
}
