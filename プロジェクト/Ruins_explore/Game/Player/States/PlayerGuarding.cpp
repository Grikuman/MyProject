/*
    ファイル名：PlayerGuarding.cpp
    　　　概要：プレイヤーの歩行状態を管理するクラス
*/
#include "pch.h"
#include "PlayerGuarding.h"
#include "Game/Player/Player.h"
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
PlayerGuarding::PlayerGuarding()
	:
    m_player{}
{
    // アニメーションを作成する
    m_animation = std::make_unique<PlayerGuardingAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerGuarding::~PlayerGuarding()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerGuarding::Initialize()
{
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerGuarding::Update()
{
    // 待機状態への移行処理
    TransitionToIdling();

    // アニメーションを更新する
    m_animation->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerGuarding::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}


//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerGuarding::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 待機状態への移行処理
//---------------------------------------------------------
void PlayerGuarding::TransitionToIdling()
{
    // キーボード入力を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // ガード入力が無ければ待機状態へ移行する
    if (!kb->C)
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}
