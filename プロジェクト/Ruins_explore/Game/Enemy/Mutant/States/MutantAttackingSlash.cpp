/*
	ファイル名：MutantAttackingSlash.cpp
	　　　概要：岩ボスの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "MutantAttackingSlash.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// 攻撃のバウンディングスフィアを取得する
//---------------------------------------------------------
DirectX::BoundingSphere MutantAttackingSlash::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantAttackingSlash::MutantAttackingSlash(Mutant* mutant)
	:
    m_mutant(mutant)
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantAttackingSlash::~MutantAttackingSlash()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantAttackingSlash::Initialize()
{
	
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantAttackingSlash::Update()
{
	// 斬りつけ攻撃の処理
	Slash();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantAttackingSlash::Render()
{

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantAttackingSlash::Finalize()
{
    
}

//---------------------------------------------------------
// 斬りつけ攻撃の処理
//---------------------------------------------------------
void MutantAttackingSlash::Slash()
{

}

//void MutantAttackingSlash::ChargingAttack()
//{
//	// 方向をプレイヤーに向ける
//	DirectX::SimpleMath::Vector3 direction = m_needleBoss->GetPlayer()->GetPosition() - m_needleBoss->GetPosition();
//	direction.Normalize();
//
//	// 突進速度を適用
//	// 突進する
//	m_needleBoss->SetVelocity(DirectX::SimpleMath::Vector3::Forward);
//	// 移動量を補正する
//	m_needleBoss->SetVelocity(m_needleBoss->GetVelocity() * -0.06f);
//	// 回転を加味して実際に移動する
//	m_needleBoss->SetPosition(
//		m_needleBoss->GetPosition() +
//		DirectX::SimpleMath::Vector3::Transform(m_needleBoss->GetVelocity(), DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_needleBoss->GetAngle())));
//
//	// 衝突判定
//	if (GetAttackBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()))
//	{
//		if (!m_needleBoss->GetPlayer()->GetInvincible())
//		{
//			m_needleBoss->GetPlayer()->SetHP(m_needleBoss->GetPlayer()->GetHP() - 1);
//			m_needleBoss->GetPlayer()->SetInvincible(true);
//			// 攻撃音
//			Audio::GetInstance()->PlaySE("EnemyAttackSE");
//			// カメラを揺らす
//			m_needleBoss->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
//		}
//	}
//	// 突進が一定距離に達したら終了
//	if (m_atackStartTime >= 120)
//	{
//		m_attackType = AttackType::Spinning;
//		m_atackStartTime = 0;
//		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
//	}
//}
