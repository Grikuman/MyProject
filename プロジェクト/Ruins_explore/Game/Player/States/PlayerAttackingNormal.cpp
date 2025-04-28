/*
    ファイル名：PlayerAttackingNormal.cpp
    　　　概要：プレイヤーの通常攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerAttackingNormal.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// 攻撃範囲を取得する
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttackingNormal::GetAttackRange()
{
    return DirectX::BoundingSphere(m_player->GetPosition(), ATTACK_DISTANCE);
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttackingNormal::PlayerAttackingNormal(Player* player)
	:
    m_player{player}
{
    // アニメーションを作成する
    m_animation = std::make_unique<PlayerAttackingNormalAnimation>(player);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttackingNormal::~PlayerAttackingNormal()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttackingNormal::Initialize()
{
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttackingNormal::Update()
{
    // 待機状態への移行処理
    TransitionToIdling();
    // アニメーションを更新する
    m_animation->Update();
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttackingNormal::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}


//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerAttackingNormal::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 待機状態への移行処理
//---------------------------------------------------------
void PlayerAttackingNormal::TransitionToIdling()
{
    if (m_animation->IsEndAnimation())
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}

