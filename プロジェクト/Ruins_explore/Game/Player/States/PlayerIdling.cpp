/*
    ファイル名：PlayerIdling.cpp
    　　　概要：プレイヤーの待機状態を管理するクラス
*/
#include "pch.h"
#include "PlayerIdling.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerIdling::PlayerIdling()
	:
    m_player{}
{
    // アニメーションを作成する
    m_animation = std::make_unique<PlayerIdlingAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerIdling::~PlayerIdling()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerIdling::Initialize()
{
    // プレイヤーを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerIdling::Update()
{
    // 待機処理
    Idling();
    // 走り状態への移行処理
    TransitionToRunning();
    // 通常攻撃状態への移行処理
    TransitionToAttackingNormal();

    // アニメーションを更新する
    m_animation->Update();
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerIdling::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}


//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerIdling::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 待機処理
//---------------------------------------------------------
void PlayerIdling::Idling()
{
    
}

//---------------------------------------------------------
// 走る状態への移行処理
//---------------------------------------------------------
void PlayerIdling::TransitionToRunning()
{
    // キーボード入力を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // 入力があれば走る状態へ移行する
    if (kb->W || kb->S || kb->A || kb->D) // 前
    {
        m_player->ChangeState(m_player->GetPlayerRunning());
    }
}

//---------------------------------------------------------
// 通常攻撃状態への移行処理
//---------------------------------------------------------
void PlayerIdling::TransitionToAttackingNormal()
{
    // キーボード入力を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    if (kb->F)
    {
        m_player->ChangeState(m_player->GetPlayerAttackingNormal());
    }
}
