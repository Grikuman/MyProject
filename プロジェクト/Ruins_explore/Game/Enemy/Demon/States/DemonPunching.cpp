/*
	ファイル名：DemonPunching.cpp
	　　　概要：ウォーロックのパンチ状態を管理するクラス
*/
#include "pch.h"
#include "DemonPunching.h"
#include "Game/Enemy/Demon/Demon.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
DemonPunching::DemonPunching(Demon* demon)
	:
    m_demon(demon)
{
	// アニメーションを作成する
	m_animation = std::make_unique<DemonPunchingAnimation>(demon);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
DemonPunching::~DemonPunching()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void DemonPunching::Initialize()
{
	// アニメーションを初期化する
	m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void DemonPunching::Update()
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
void DemonPunching::Render()
{
	// アニメーションを描画する
	m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void DemonPunching::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// 斬りつけの処理
//---------------------------------------------------------
void DemonPunching::Punching()
{
	using namespace DirectX::SimpleMath;

	// ミュータントがダメージを与えられる状態であれば通過
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // プレイヤーが無敵でなければ通過
	if (m_demon->GetPlayer()->GetInvincible())
	{
		return;
	}

	// プレイヤーの位置を取得する
	Vector3 playerPos = m_demon->GetPlayer()->GetPosition();
	// ミュータントの位置を取得する
	Vector3 mutantPos = m_demon->GetPosition();
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
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_demon->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-方向が「前」

	// mutantからプレイヤーへのベクトル
	Vector3 toPlayer = m_demon->GetPlayer()->GetPosition() - m_demon->GetPosition();
	toPlayer.Normalize();

	// 正面方向とプレイヤーへのベクトルの内積
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// 前方約60度以内
	if (dot > ATTACK_DOT)
	{
		m_demon->GetPlayer()->SetHP(m_demon->GetPlayer()->GetHP() - 1);
		m_demon->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		m_demon->GetPlayer()->GetCamera()->StartShake(CAMERA_INTENSITY, CAMERA_DURATION);
	}
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void DemonPunching::TransitionToWalking()
{
	// アニメーションが終了したら待機状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		m_demon->ChangeState(m_demon->GetDemonWalking());
	}
}