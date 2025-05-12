/*
	ファイル名：MutantSlashing.cpp
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#include "pch.h"
#include "MutantSlashing.h"
#include "Game/Enemy/Mutant/Mutant.h"
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
MutantSlashing::MutantSlashing()
	:
    m_mutant{},
	m_player{}
{
	// アニメーションを作成する
	m_animation = std::make_unique<MutantSlashingAnimation>();
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
	// プレイヤーのポインタを取得する
	m_mutant = static_cast<Mutant*>(EventMessenger::ExecuteGetter(GetterList::GetMutant));
	// プレイヤーのポインタを取得する
	m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
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
	m_animation->Update();
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
	if (m_player->GetInvincible())
	{
		return;
	}

	// プレイヤーの位置を取得する
	Vector3 playerPos = m_player->GetPosition();
	// ミュータントの位置を取得する
	Vector3 mutantPos = m_mutant->GetPosition();
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
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_mutant->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-方向が「前」

	// mutantからプレイヤーへのベクトル
	Vector3 toPlayer = m_player->GetPosition() - m_mutant->GetPosition();
	toPlayer.Normalize();

	// 正面方向とプレイヤーへのベクトルの内積
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// 前方約60度以内
	if (dot > ATTACK_DOT)
	{
		// ダメージを与える
		m_player->SetHP(m_player->GetHP() - 1);
		m_player->SetInvincible(true);
		// 効果音
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		// カメラを振動させる
		std::pair<float, float> shakeparams = { CAMERA_INTENSITY,CAMERA_DURATION };
		EventMessenger::Execute(EventList::ShakeCamera, &shakeparams);
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