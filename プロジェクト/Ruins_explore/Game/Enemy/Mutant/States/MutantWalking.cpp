/*
    ファイル名：MutantWalking.cpp
    　　　概要：岩ボスの探索状態を管理するクラス
*/
#include "pch.h"
#include "MutantWalking.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantWalking::MutantWalking(Mutant* mutant)
	:
    m_mutant(mutant)
{
    // アニメーションを作成する
    m_animation = std::make_unique<MutantWalkingAnimation>(mutant);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantWalking::~MutantWalking()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantWalking::Initialize()
{
    // アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantWalking::Update()
{
    // 歩き処理
    Walking();
    // 突進状態への移行処理
    TransitionToRushing();
    // 斬りつけ状態への移行処理
    TransitionToSlashing();

    // アニメーションを更新する
    m_animation->Update(0.016f);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantWalking::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantWalking::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantWalking::Walking()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    // ミュータントの位置を取得する
    Vector3 tunomaruPosition = m_mutant->GetPosition();
    // プレイヤーとの距離を計算する
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // プレイヤーへの方向を計算する
    Vector3 directionToPlayer = playerPosition - tunomaruPosition;
    directionToPlayer.Normalize(); // 正規化して方向ベクトルにする

    // ミュータントの回転をプレイヤーに向ける
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // 速度を設定する
    m_mutant->AddVelocity(directionToPlayer);
    m_mutant->ApplyVelocity(0.08f);
    // 位置を設定する
    m_mutant->SetPosition(tunomaruPosition + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// 突進状態への移行処理
//---------------------------------------------------------
void MutantWalking::TransitionToRushing()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_mutant->GetPlayer()->GetPosition();
    // ミュータントの現在位置を取得する
    Vector3 mutantPos = m_mutant->GetPosition();
    // プレイヤーとミュータントの距離を計算する
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);

    // 一定距離以上プレイヤーが離れた場合
    if (distanceToPlayer >= 10)
    {
        // 突撃状態へ移行する
        m_mutant->ChangeState(m_mutant->GetMutantRushing());
    }
}

//---------------------------------------------------------
// 斬りつけ状態への移行処理
//---------------------------------------------------------
void MutantWalking::TransitionToSlashing()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    // ミュータントの現在位置を取得する
    Vector3 tunomaruPosition = m_mutant->GetPosition();
    // プレイヤーとの距離を計算する
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // 一定距離以内にプレイヤーがいた場合
    if (distanceToPlayer <= 5)
    {
        // 斬りつけ状態へ移行する
        m_mutant->ChangeState(m_mutant->GetMutantSlashing());
    }
}
