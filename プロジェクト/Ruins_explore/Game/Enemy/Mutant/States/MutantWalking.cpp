/*
    ファイル名：MutantWalking.cpp
    　　　概要：岩ボスの探索状態を管理するクラス
*/
#include "pch.h"
#include "MutantWalking.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantWalking::MutantWalking()
	:
    m_mutant{},
    m_player{}
{
    // アニメーションを作成する
    m_animation = std::make_unique<MutantWalkingAnimation>();
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
    // ミュータントのポインタを取得する
    m_mutant = static_cast<Mutant*>(EventMessenger::ExecuteGetter(GetterList::GetMutant));
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
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
    m_animation->Update();
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
    Vector3 playerPos = m_player->GetPosition();
    // ミュータントの位置を取得する
    Vector3 mutantPos = m_mutant->GetPosition();

    // プレイヤーへの方向を計算する
    Vector3 directionToPlayer = playerPos - mutantPos;
    directionToPlayer.Normalize(); // 正規化して方向ベクトルにする
    // ミュータントの回転をプレイヤーに向ける
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // 速度を設定する
    m_mutant->AddVelocity(directionToPlayer);
    m_mutant->ApplyVelocity(APPLY_VELOCITY);
    // 位置を設定する
    m_mutant->SetPosition(mutantPos + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// 突進状態への移行処理
//---------------------------------------------------------
void MutantWalking::TransitionToRushing()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_player->GetPosition();
    // ミュータントの現在位置を取得する
    Vector3 mutantPos = m_mutant->GetPosition();
    // プレイヤーとミュータントの距離を計算する
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);

    // 一定距離以上プレイヤーが離れた場合
    if (distanceToPlayer >= RUSHING_DISTANCE)
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
    Vector3 playerPosition = m_player->GetPosition();
    // ミュータントの現在位置を取得する
    Vector3 tunomaruPosition = m_mutant->GetPosition();
    // プレイヤーとの距離を計算する
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // 一定距離以内にプレイヤーがいた場合
    if (distanceToPlayer <= SLASHING_DISTANCE)
    {
        // 斬りつけ状態へ移行する
        m_mutant->ChangeState(m_mutant->GetMutantSlashing());
    }
}
