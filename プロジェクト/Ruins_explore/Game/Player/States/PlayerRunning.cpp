/*
    ファイル名：PlayerRunning.cpp
    　　　概要：プレイヤーの走り状態を管理するクラス
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerRunning.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerRunning::PlayerRunning()
	:
    m_player{}
{
    // アニメーションを作成する
    m_animation = std::make_unique<PlayerRunningAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerRunning::~PlayerRunning()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerRunning::Initialize()
{
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerRunning::Update()
{
    // 走る処理
    Running();
    // 待機状態への移行処理
    TransitionToIdling();
    // 回避状態への移行処理
    TransitionToRolling();
    // 通常攻撃状態への移行処理
    TransitionToAttackingNormal();
    // 向きの処理
    Direction();

    // アニメーションを更新する
    m_animation->Update();
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerRunning::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}


//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerRunning::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 走る処理
//---------------------------------------------------------
void PlayerRunning::Running()
{
    using namespace DirectX::SimpleMath;
    // キーボード入力を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // 入力方向を取得して、向きに応じて移動する
    if (kb->W) // 前
    {
        m_player->SetVelocity(Vector3::Forward);
    }
    if (kb->S) // 後
    {
        m_player->SetVelocity(Vector3::Backward);
    }
    if (kb->A) // 左
    {
        m_player->SetVelocity(Vector3::Left);
    }
    if (kb->D) // 右
    {
        m_player->SetVelocity(Vector3::Right);
    }

    // 移動速度を補正
    m_player->ApplyVelocity(APPLY_VELOCITY);
    // 移動させる
    m_player->SetPosition(m_player->GetPosition() + DirectX::SimpleMath::Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// 待機状態への移行処理
//---------------------------------------------------------
void PlayerRunning::TransitionToIdling()
{
    // キーボード入力を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();
    // 入力が無ければ待機状態へ移行する
    if (kb->W || kb->S || kb->A || kb->D)
    {
        return;
    }
    m_player->ChangeState(m_player->GetPlayerIdling());
}

//---------------------------------------------------------
// 回避状態への移行処理
//---------------------------------------------------------
void PlayerRunning::TransitionToRolling()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // スタミナがある場合
    if (m_player->GetStamina() >= 1)
    {
        // スペースキーを押したら
        if (kb->Space)
        {
            // スタミナを消費する
            m_player->SetStamina(m_player->GetStamina() - 1);
            // ダッシュ音
            Audio::GetInstance()->PlaySE("DashSE");
            // 回避状態に変更する
            m_player->ChangeState(m_player->GetPlayerRolling());
        }
    }
}

//---------------------------------------------------------
// 通常攻撃状態への移行処理
//---------------------------------------------------------
void PlayerRunning::TransitionToAttackingNormal()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    if (kb->F)
    {
        m_player->ChangeState(m_player->GetPlayerAttackingNormal());
    }
}

//---------------------------------------------------------
// 向きの処理
//---------------------------------------------------------
void PlayerRunning::Direction()
{
    using namespace DirectX::SimpleMath;
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // 入力方向を取得して、向きを設定する
    if (kb->W) // 前
    {
        m_player->SetDirection(Vector3::Forward);
    }
    if (kb->S) // 後
    {
        m_player->SetDirection(Vector3::Backward);
    }
    if (kb->A) // 左
    {
        m_player->SetDirection(Vector3::Left);
    }
    if (kb->D) // 右
    {
        m_player->SetDirection(Vector3::Right);
    }
}
