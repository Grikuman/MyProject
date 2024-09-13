#pragma once
#include "pch.h"
#include "Game/Effect/PlayerEffectManager.h"
#include "Game/Player/Player.h"

// コンストラクタ
PlayerEffectManager::PlayerEffectManager(Player* player)
    :
    m_player{player},
    m_invincibleEffect{}
{
    
}
// デストラクタ
PlayerEffectManager::~PlayerEffectManager()
{

}

// 初期化
void PlayerEffectManager::Initialize()
{
    // 無敵エフェクトを作成する
    m_invincibleEffect = std::make_unique<InvincibleEffect>(m_player);
    // 無敵エフェクトを初期化する
    m_invincibleEffect->Initialize();
}

// 更新する
void PlayerEffectManager::Update()
{
    m_invincibleEffect->Update();
}

// 描画する
void PlayerEffectManager::Render()
{
    m_invincibleEffect->Render();
}

// 後処理する
void PlayerEffectManager::Finalize()
{
    m_invincibleEffect->Finalize();
}
