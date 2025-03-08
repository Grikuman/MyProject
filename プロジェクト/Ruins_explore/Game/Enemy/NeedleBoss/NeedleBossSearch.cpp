/*
    ファイル名：NeedleBossSearch.cpp
    　　　概要：岩ボスの探索状態を管理するクラス
*/
#include "pch.h"
#include "NeedleBoss.h"
#include "NeedleBossSearch.h"
#include "Game/Player/Player.h"

#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
NeedleBossSearch::NeedleBossSearch(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
NeedleBossSearch::~NeedleBossSearch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void NeedleBossSearch::Initialize()
{
    
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void NeedleBossSearch::Update()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_needleBoss->GetPlayer()->GetPosition();

    // 岩ボスの現在位置を取得
    Vector3 tunomaruPosition = m_needleBoss->GetPosition();

    // プレイヤーとの距離を計算
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // 距離が20.0f以内の場合、プレイヤーを追いかける
    if (distanceToPlayer <= 20.0f)
    {
        // プレイヤーへの方向を計算
        Vector3 directionToPlayer = playerPosition - tunomaruPosition;
        directionToPlayer.Normalize(); // 正規化して方向ベクトルにする

        // 岩ボスの回転をプレイヤーに向ける
        float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
        m_needleBoss->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

        // 速度を設定
        m_needleBoss->AddVelocity(directionToPlayer);
        m_needleBoss->ApplyVelocity(0.05f);

        m_needleBoss->SetPosition(tunomaruPosition + m_needleBoss->GetVelocity());
    }

    // 探索から攻撃へ
    SearchToAttack();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void NeedleBossSearch::Render()
{

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void NeedleBossSearch::Finalize()
{
    
}

//---------------------------------------------------------
// 探索から攻撃へ
//---------------------------------------------------------
void NeedleBossSearch::SearchToAttack()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_needleBoss->GetPlayer()->GetPosition();
    // 岩ボスの現在位置を取得
    Vector3 tunomaruPosition = m_needleBoss->GetPosition();
    // プレイヤーとの距離を計算
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    if (distanceToPlayer <= 5)
    {
        m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossAttack());
    }
}
