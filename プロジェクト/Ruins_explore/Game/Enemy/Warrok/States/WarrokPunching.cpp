/*
	ファイル名：WarrokPunching.cpp
	　　　概要：ウォーロックのパンチ状態を管理するクラス
*/
#include "pch.h"
#include "WarrokPunching.h"
#include "Game/Enemy/Warrok/Warrok.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
WarrokPunching::WarrokPunching(Warrok* warrok)
	:
    m_warrok(warrok)
{
	// アニメーションを作成する
	m_animation = std::make_unique<WarrokPunchingAnimation>(warrok);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
WarrokPunching::~WarrokPunching()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void WarrokPunching::Initialize()
{
	// アニメーションを初期化する
	m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void WarrokPunching::Update()
{
	// パンチの処理
	Punching();
	// 歩き状態への移行処理
	TransitionToWalking();
	
	// アニメーションを更新する
	m_animation->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void WarrokPunching::Render()
{
	// アニメーションを描画する
	m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void WarrokPunching::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// 斬りつけの処理
//---------------------------------------------------------
void WarrokPunching::Punching()
{
	using namespace DirectX::SimpleMath;

	// ミュータントがダメージを与えられる状態であれば通過
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // プレイヤーが無敵でなければ通過
	if (m_warrok->GetPlayer()->GetInvincible())
	{
		return;
	}

	// プレイヤーの位置を取得する
	Vector3 playerPos = m_warrok->GetPlayer()->GetPosition();
	// ミュータントの位置を取得する
	Vector3 mutantPos = m_warrok->GetPosition();
	// プレイヤーとミュータントの距離を計算する
	float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);
	// 一定距離以内にプレイヤーがいる場合通過
	if (distanceToPlayer > ATTACK_DISTANCE)
	{
		return;
	}

	//=====================================================
	// * ダメージ処理 *
	//=====================================================
	
	// mutantの前方向ベクトルをQuaternionから求める
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_warrok->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-方向が「前」

	// mutantからプレイヤーへのベクトル
	Vector3 toPlayer = m_warrok->GetPlayer()->GetPosition() - m_warrok->GetPosition();
	toPlayer.Normalize();

	// 正面方向とプレイヤーへのベクトルの内積
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// 前方約60度以内
	if (dot > ATTACK_DOT)
	{
		m_warrok->GetPlayer()->SetHP(m_warrok->GetPlayer()->GetHP() - 1);
		m_warrok->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		//m_warrok->GetPlayer()->GetCamera()->StartShake(CAMERA_INTENSITY, CAMERA_DURATION);
		// カメラを振動させる
		std::pair<float, float> shakeparams { CAMERA_INTENSITY, CAMERA_DURATION };
		EventMessenger::Execute(EventList::ShakeCamera, &shakeparams);
	}
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void WarrokPunching::TransitionToWalking()
{
	// アニメーションが終了したら待機状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		m_warrok->ChangeState(m_warrok->GetWarrokKicking());
	}
}