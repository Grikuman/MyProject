/*
    ファイル名：RockBossSearch.cpp
    　　　概要：岩ボスの探索状態を管理するクラス
*/
#include "pch.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "RockBossSearch.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
RockBossSearch::RockBossSearch(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
RockBossSearch::~RockBossSearch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void RockBossSearch::Initialize()
{
    m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void RockBossSearch::Update()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_rockBoss->GetPlayer()->GetPosition();

    // 岩ボスの現在位置を取得
    Vector3 tunomaruPosition = m_rockBoss->GetPosition();

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
        m_rockBoss->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

        // 速度を設定
        m_rockBoss->AddVelocity(directionToPlayer);
        m_rockBoss->ApplyVelocity(0.05f);

        m_rockBoss->SetPotision(tunomaruPosition + m_rockBoss->GetVelocity());
    }

    // 探索から攻撃へ
    SearchToAttack();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void RockBossSearch::Finalize()
{
    
}

//---------------------------------------------------------
// 探索から攻撃へ
//---------------------------------------------------------
void RockBossSearch::SearchToAttack()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_rockBoss->GetPlayer()->GetPosition();
    // 岩ボスの現在位置を取得
    Vector3 tunomaruPosition = m_rockBoss->GetPosition();
    // プレイヤーとの距離を計算
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    if (distanceToPlayer <= 5)
    {
        m_rockBoss->ChangeState(m_rockBoss->GetRockBossAttack());
    }
}
