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
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
NeedleBossAttack::NeedleBossAttack(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{},
	m_attackType{AttackType::Charging}
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
	m_atackStartTime++;

	switch (m_attackType)
	{
		case AttackType::Spinning:
			// 回転攻撃
			SpinningAttack();
			break;
		case AttackType::Charging:
			// 突進攻撃
			ChargingAttack();
			break;
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
				// 攻撃音
				Audio::GetInstance()->PlaySE("EnemyAttackSE");
				// カメラを揺らす
				m_needleBoss->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
			}
		}
	}

	if (m_rotateCnt >= 360.f)
	{
		// 突進攻撃に切り替える
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_attackType = AttackType::Charging;
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
	}
}

void NeedleBossAttack::ChargingAttack()
{
	// 方向をプレイヤーに向ける
	DirectX::SimpleMath::Vector3 direction = m_needleBoss->GetPlayer()->GetPosition() - m_needleBoss->GetPosition();
	direction.Normalize();

	// 突進速度を適用
	// 突進する
	m_needleBoss->SetVelocity(DirectX::SimpleMath::Vector3::Forward);
	// 移動量を補正する
	m_needleBoss->SetVelocity(m_needleBoss->GetVelocity() * -0.06f);
	// 回転を加味して実際に移動する
	m_needleBoss->SetPosition(
		m_needleBoss->GetPosition() +
		DirectX::SimpleMath::Vector3::Transform(m_needleBoss->GetVelocity(), DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_needleBoss->GetAngle())));

	// 衝突判定
	if (GetAttackBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()))
	{
		if (!m_needleBoss->GetPlayer()->GetInvincible())
		{
			m_needleBoss->GetPlayer()->SetHP(m_needleBoss->GetPlayer()->GetHP() - 1);
			m_needleBoss->GetPlayer()->SetInvincible(true);
			// 攻撃音
			Audio::GetInstance()->PlaySE("EnemyAttackSE");
			// カメラを揺らす
			m_needleBoss->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
		}
	}
	// 突進が一定距離に達したら終了
	if (m_atackStartTime >= 120)
	{
		m_attackType = AttackType::Spinning;
		m_atackStartTime = 0;
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
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
