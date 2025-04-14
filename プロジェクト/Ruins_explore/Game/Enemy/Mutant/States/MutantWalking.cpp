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
    // 探索から攻撃へ
    SearchToAttack();

    // アニメーションを更新する
    m_animation->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantWalking::Render()
{

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantWalking::Finalize()
{
    
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
    m_mutant->ApplyVelocity(0.05f);
    // 位置を設定する
    m_mutant->SetPosition(tunomaruPosition + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// 探索から攻撃へ
//---------------------------------------------------------
void MutantWalking::SearchToAttack()
{
    //using namespace DirectX::SimpleMath;

    //// プレイヤーの位置を取得する
    //Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    //// ミュータントの現在位置を取得する
    //Vector3 tunomaruPosition = m_mutant->GetPosition();
    //// プレイヤーとの距離を計算する
    //float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    //if (distanceToPlayer <= 5)
    //{
    //    m_mutant->ChangeState(m_mutant->GetNeedleBossAttack());
    //}
}
