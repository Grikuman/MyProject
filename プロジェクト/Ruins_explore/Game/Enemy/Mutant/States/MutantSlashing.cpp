/*
	ファイル名：MutantSlashing.cpp
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#include "pch.h"
#include "MutantSlashing.h"
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
DirectX::BoundingSphere MutantSlashing::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantSlashing::MutantSlashing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	// アニメーションを作成する
	m_animation = std::make_unique<MutantSlashingAnimation>(mutant);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantSlashing::~MutantSlashing()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantSlashing::Initialize()
{
	// アニメーションを初期化する
	m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantSlashing::Update()
{
	// 斬りつけの処理
	Slashing();
	// 歩き状態への移行処理
	TransitionToWalking();
	
	// アニメーションを更新する
	m_animation->Update(0.016f);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantSlashing::Render()
{
	// アニメーションを描画する
	m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantSlashing::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// 斬りつけの処理
//---------------------------------------------------------
void MutantSlashing::Slashing()
{
	using namespace DirectX::SimpleMath;

	// ミュータントがダメージを与えられる状態であれば通過
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // プレイヤーが無敵でなければ通過
	if (!m_mutant->GetPlayer()->GetInvincible())
	{
		return;
	}

	//=====================================================
	// * ダメージ処理 *
	//=====================================================

	// プレイヤーの位置を取得する
	Vector3 playerPos = m_mutant->GetPlayer()->GetPosition();
	// ミュータントの位置を取得する
	Vector3 mutantPos = m_mutant->GetPosition();
	// プレイヤーとミュータントの距離を計算する
	float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);

	// 一定距離以内プレイヤーが離れた場合
	if (distanceToPlayer >= 10)
	{
		
	}
	
	// mutantの前方向ベクトルをQuaternionから求める
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_mutant->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-方向が「前」

	// mutantからプレイヤーへのベクトル
	Vector3 toPlayer = m_mutant->GetPlayer()->GetPosition() - m_mutant->GetPosition();
	toPlayer.Normalize();

	// 正面方向とプレイヤーへのベクトルの内積
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// 前方約60度以内
	if (dot > 0.5f)
	{
		m_mutant->GetPlayer()->SetHP(m_mutant->GetPlayer()->GetHP() - 1);
		m_mutant->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		m_mutant->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
	}
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void MutantSlashing::TransitionToWalking()
{
	// アニメーションが終了したら待機状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
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
