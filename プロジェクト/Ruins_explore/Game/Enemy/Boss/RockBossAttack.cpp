/*
	ファイル名：RockBossAttack.cpp
	　　　概要：岩ボスの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "RockBoss.h"
#include "RockBossAttack.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Collision.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
RockBossAttack::RockBossAttack(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
RockBossAttack::~RockBossAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void RockBossAttack::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void RockBossAttack::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// 攻撃までの猶予時間をカウントする
	m_atackStartTime++;

	SpinningAttack();

	// 
	if (m_rotateCnt >= 360.f)
	{
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossDown());
	}
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void RockBossAttack::Finalize()
{
    
}

//---------------------------------------------------------
// 回転攻撃
//---------------------------------------------------------
void RockBossAttack::SpinningAttack()
{
	using namespace DirectX::SimpleMath;

	// 回転させる
	if (m_atackStartTime >= ATACKSTART_TIME)
	{
		m_rotateCnt += 10.f;
		Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(20.0f));
		m_rockBoss->AddAngle(rotation);

		// プレイヤーが攻撃範囲内にいる　かつ　プレイヤーがダメージを受けない部分にいない
		if (GetAttackBoundingSphere().Intersects(m_rockBoss->GetPlayer()->GetBoundingSphere()) &&
			!GetNoDamageBoundingSphere().Intersects(m_rockBoss->GetPlayer()->GetBoundingSphere()))
		{
			// プレイヤーが無敵でなければ
			if (!m_rockBoss->GetPlayer()->GetInvincible())
			{
				// プレイヤーへダメージ処理
				m_rockBoss->GetPlayer()->SetHP(m_rockBoss->GetPlayer()->GetHP() - 1);
				// プレイヤーを無敵に
				m_rockBoss->GetPlayer()->SetInvincible(true);
			}
		}
	}
}

DirectX::BoundingSphere RockBossAttack::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_rockBoss->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center,radius);
}

DirectX::BoundingSphere RockBossAttack::GetNoDamageBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_rockBoss->GetPosition();
	float radius = 1.f;
	return DirectX::BoundingSphere(center,radius);
}
