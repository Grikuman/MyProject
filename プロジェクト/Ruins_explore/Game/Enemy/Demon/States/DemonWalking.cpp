/*
    ファイル名：DemonWalking.cpp
    　　　概要：ウォーロックの歩き状態を管理するクラス
*/
#include "pch.h"
#include "DemonWalking.h"
#include "Game/Enemy/Demon/Demon.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
DemonWalking::DemonWalking(Demon* demon)
	:
    m_demon(demon)
{
    // アニメーションを作成する
    m_animation = std::make_unique<DemonWalkingAnimation>(demon);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
DemonWalking::~DemonWalking()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void DemonWalking::Initialize()
{
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void DemonWalking::Update()
{
    // 歩き処理
    Walking();
    // パンチ状態への移行処理
    TransitionToPunching();

    // アニメーションを更新する
    m_animation->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void DemonWalking::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void DemonWalking::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void DemonWalking::Walking()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_demon->GetPlayer()->GetPosition();
    // ミュータントの位置を取得する
    Vector3 DemonPos = m_demon->GetPosition();

    // プレイヤーへの方向を計算する
    Vector3 directionToPlayer = playerPos - DemonPos;
    directionToPlayer.Normalize(); // 正規化して方向ベクトルにする
    // ミュータントの回転をプレイヤーに向ける
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_demon->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // 速度を設定する
    m_demon->AddVelocity(directionToPlayer);
    m_demon->ApplyVelocity(APPLY_VELOCITY);
    // 位置を設定する
    m_demon->SetPosition(DemonPos + m_demon->GetVelocity());
}

//---------------------------------------------------------
// パンチ状態への移行処理
//---------------------------------------------------------
void DemonWalking::TransitionToPunching()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPosition = m_demon->GetPlayer()->GetPosition();
    // ミュータントの現在位置を取得する
    Vector3 tunomaruPosition = m_demon->GetPosition();
    // プレイヤーとの距離を計算する
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // 一定距離以内にプレイヤーがいた場合
    if (distanceToPlayer <= PUNCHING_DISTANCE)
    {
        // 斬りつけ状態へ移行する
        m_demon->ChangeState(m_demon->GetDemonPunching());
    }
}
