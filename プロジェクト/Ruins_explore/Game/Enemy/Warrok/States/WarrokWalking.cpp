/*
    ファイル名：WarrokWalking.cpp
    　　　概要：ウォーロックの歩き状態を管理するクラス
*/
#include "pch.h"
#include "WarrokWalking.h"
#include "Game/Enemy/Warrok/Warrok.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
WarrokWalking::WarrokWalking(Warrok* warrok)
	:
    m_warrok(warrok)
{
    // アニメーションを作成する
    m_animation = std::make_unique<WarrokWalkingAnimation>(warrok);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
WarrokWalking::~WarrokWalking()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void WarrokWalking::Initialize()
{
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void WarrokWalking::Update()
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
void WarrokWalking::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void WarrokWalking::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void WarrokWalking::Walking()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_warrok->GetPlayer()->GetPosition();
    // ミュータントの位置を取得する
    Vector3 warrokPos = m_warrok->GetPosition();

    // プレイヤーへの方向を計算する
    Vector3 directionToPlayer = playerPos - warrokPos;
    directionToPlayer.Normalize(); // 正規化して方向ベクトルにする
    // ミュータントの回転をプレイヤーに向ける
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_warrok->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // 速度を設定する
    m_warrok->AddVelocity(directionToPlayer);
    m_warrok->ApplyVelocity(APPLY_VELOCITY);
    // 位置を設定する
    m_warrok->SetPosition(warrokPos + m_warrok->GetVelocity());
}

//---------------------------------------------------------
// パンチ状態への移行処理
//---------------------------------------------------------
void WarrokWalking::TransitionToPunching()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPosition = m_warrok->GetPlayer()->GetPosition();
    // ミュータントの現在位置を取得する
    Vector3 tunomaruPosition = m_warrok->GetPosition();
    // プレイヤーとの距離を計算する
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // 一定距離以内にプレイヤーがいた場合
    if (distanceToPlayer <= PUNCHING_DISTANCE)
    {
        // 斬りつけ状態へ移行する
        m_warrok->ChangeState(m_warrok->GetWarrokPunching());
    }
}
