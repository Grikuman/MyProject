/*
    ファイル名：PlayerRolling.cpp
    　　　概要：プレイヤーの回避状態を管理するクラス
*/
#include "pch.h"
#include "PlayerRolling.h"
#include "Game/Player/Player.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerRolling::PlayerRolling()
	:
    m_player{}
{
    // アニメーションを作成する
    m_animation = std::make_unique<PlayerRollingAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerRolling::~PlayerRolling()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerRolling::Initialize()
{
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerRolling::Update()
{
    // 回避処理
    Rolling();
    // 待機状態への移行処理
    TransitionToIdling();

    // アニメーションを更新する
    m_animation->Update();
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerRolling::Render()
{
   // アニメーションを描画する
    m_animation->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerRolling::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 回避処理
//---------------------------------------------------------
void PlayerRolling::Rolling()
{
    // 向きを取得する
    DirectX::SimpleMath::Vector3 direction = m_player->GetDirection();
    // 移動速度を設定する
    m_player->SetVelocity(direction);
    // 移動速度を補正する
    m_player->ApplyVelocity(APPLY_VELOCITY);
    // 移動する
    m_player->SetPosition(m_player->GetPosition() + DirectX::SimpleMath::Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// 待機状態への移行処理
//---------------------------------------------------------
void PlayerRolling::TransitionToIdling()
{
    // アニメーションが終了したら待機状態へ移行する
    if (m_animation->IsEndAnimation())
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}