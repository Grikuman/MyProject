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

    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_rockBoss->GetPlayer()->GetPosition();
    // ボスの現在の位置を取得する
    Vector3 RockBossPos = m_rockBoss->GetPosition();
    // プレイヤーとの距離を計算する
    float distance = Vector3::Distance(playerPos, RockBossPos);

    // 距離が5.f以内ならアタック状態へ移行する
    if (distance < 3.0f)
    {
        // プレイヤーへの向きを計算する
        Vector3 direction = playerPos - RockBossPos;
        direction.Normalize();
        float newAngle = atan2f(-direction.x, -direction.z);
        m_rockBoss->SetAngle(XMConvertToDegrees(newAngle));
        // アタック状態へ移行する
        m_rockBoss->ChangeState(m_rockBoss->GetRockBossAttack());
        return;
    }

    // 距離が20.f以内ならプレイヤーを追いかける
    if (distance < 20.0f)
    {
        Vector3 direction = playerPos - RockBossPos;
        direction.Normalize();
        float newAngle = atan2f(-direction.x, -direction.z);
        m_rockBoss->SetAngle(XMConvertToDegrees(newAngle));
        m_rockBoss->SetPotision(RockBossPos + direction * 0.04f);
    }
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void RockBossSearch::Finalize()
{
    
}
