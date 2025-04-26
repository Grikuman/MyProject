/*
	ファイル名：MutantRushing.cpp
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#include "pch.h"
#include "MutantRushing.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

DirectX::BoundingSphere MutantRushing::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantRushing::MutantRushing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	// アニメーションを作成する
    m_animation = std::make_unique<MutantRushingAnimation>(mutant);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantRushing::~MutantRushing()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantRushing::Initialize()
{
	// アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantRushing::Update()
{
    // 突進処理
    Rushing();
    // 歩き状態への移行処理
    TransitionToWalking();

    // アニメーションを更新する
    m_animation->Update(0.016f);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantRushing::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantRushing::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 突進処理
//---------------------------------------------------------
void MutantRushing::Rushing()
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
    m_mutant->ApplyVelocity(0.15f);
    // 位置を設定する
    m_mutant->SetPosition(tunomaruPosition + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void MutantRushing::TransitionToWalking()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_mutant->GetPlayer()->GetPosition(); 
    // ミュータントの現在位置を取得する
    Vector3 mutantPos = m_mutant->GetPosition(); 
    // プレイヤーとミュータントの距離を計算する
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos); 

    // 一定距離内にプレイヤーがいる場合
    if (distanceToPlayer <= 10) 
    {
        // 歩き状態へ移行する
        m_mutant->ChangeState(m_mutant->GetMutantWalking());
    }
}
