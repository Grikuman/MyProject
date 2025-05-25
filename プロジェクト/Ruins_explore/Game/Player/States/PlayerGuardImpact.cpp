/*
    ファイル名：PlayerGuardImpact.cpp
    　　　概要：プレイヤーのガード衝撃状態を管理するクラス
*/
#include "pch.h"
#include "PlayerGuardImpact.h"
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
PlayerGuardImpact::PlayerGuardImpact()
	:
    m_player{}
{
    // アニメーションを作成する
    m_animation = std::make_unique<PlayerGuardImpactAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerGuardImpact::~PlayerGuardImpact()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerGuardImpact::Initialize()
{
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerGuardImpact::Update()
{
    // アニメーションを更新する
    m_animation->Update();

    // 待機状態への移行処理
    TransitionToIdling();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerGuardImpact::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}


//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerGuardImpact::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 待機状態への移行処理
//---------------------------------------------------------
void PlayerGuardImpact::TransitionToIdling()
{
    if (m_animation->IsEndAnimation())
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}
