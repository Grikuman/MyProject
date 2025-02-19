/*
	ファイル名：NeedleBossAttack.cpp
	　　　概要：岩ボスの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "NeedleBoss.h"
#include "NeedleBossAttack.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
NeedleBossAttack::NeedleBossAttack(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
NeedleBossAttack::~NeedleBossAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void NeedleBossAttack::Initialize()
{
	
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void NeedleBossAttack::Update()
{
	// 攻撃までの猶予時間をカウントする
	m_atackStartTime++;

	SpinningAttack();

	// 
	if (m_rotateCnt >= 360.f)
	{
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void NeedleBossAttack::Render()
{
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void NeedleBossAttack::Finalize()
{
    
}

//---------------------------------------------------------
// 回転攻撃
//---------------------------------------------------------
void NeedleBossAttack::SpinningAttack()
{
	using namespace DirectX::SimpleMath;

	// 回転させる
	if (m_atackStartTime >= ATACKSTART_TIME)
	{
		m_rotateCnt += 10.f;
		Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(20.0f));
		m_needleBoss->AddAngle(rotation);

		// プレイヤーが攻撃範囲内にいる　かつ　プレイヤーがダメージを受けない部分にいない
		if (GetAttackBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()) &&
			!GetNoDamageBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()))
		{
			// プレイヤーが無敵でなければ
			if (!m_needleBoss->GetPlayer()->GetInvincible())
			{
				// プレイヤーへダメージ処理
				m_needleBoss->GetPlayer()->SetHP(m_needleBoss->GetPlayer()->GetHP() - 1);
				// プレイヤーを無敵に
				m_needleBoss->GetPlayer()->SetInvincible(true);
			}
		}
	}
}

DirectX::BoundingSphere NeedleBossAttack::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_needleBoss->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center,radius);
}

DirectX::BoundingSphere NeedleBossAttack::GetNoDamageBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_needleBoss->GetPosition();
	float radius = 1.f;
	return DirectX::BoundingSphere(center,radius);
}
