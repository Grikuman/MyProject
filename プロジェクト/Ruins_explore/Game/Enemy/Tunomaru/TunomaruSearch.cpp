/*
    ファイル名：TunomaruSearch.cpp
    　　　概要：つのまるの索敵状態を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruSearch.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruSearch::TunomaruSearch(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruSearch::~TunomaruSearch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruSearch::Initialize()
{
    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruSearch::Update()
{
    // プレイヤーを追いかける
    ChasePlayer();
    // 探索から攻撃へ
    SearchToAttack();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruSearch::Render()
{

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruSearch::Finalize()
{
    
}

//---------------------------------------------------------
// プレイヤーを追いかける
//---------------------------------------------------------
void TunomaruSearch::ChasePlayer()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_tunomaru->GetPlayer()->GetPosition();
    // つのまるの現在位置を取得
    Vector3 tunomaruPosition = m_tunomaru->GetPosition();
    // プレイヤーとの距離を計算
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // プレイヤーへの方向を計算
    Vector3 directionToPlayer = playerPosition - tunomaruPosition;
    directionToPlayer.Normalize(); // 正規化して方向ベクトルにする

    // つのまるの回転をプレイヤーに向ける
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_tunomaru->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // 速度を設定する
    m_tunomaru->AddVelocity(directionToPlayer);
    m_tunomaru->ApplyVelocity(0.05f);// つのまるを移動させる
    // 位置を設定する
    m_tunomaru->SetPosition(tunomaruPosition + m_tunomaru->GetVelocity());
}

//---------------------------------------------------------
// 探索から攻撃へ
//---------------------------------------------------------
void TunomaruSearch::SearchToAttack()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_tunomaru->GetPlayer()->GetPosition();

    // つのまるの現在位置を取得
    Vector3 tunomaruPosition = m_tunomaru->GetPosition();

    // プレイヤーとの距離を計算
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // 距離が20.0f以内の場合、攻撃に移行する
    if (distanceToPlayer <= 5.0f)
    {
        m_tunomaru->ChangeState(m_tunomaru->GetTunomaruAttack());
    }
}