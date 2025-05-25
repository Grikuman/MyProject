/*
	ファイル名：MutantJumping.cpp
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#include "pch.h"
#include "MutantJumping.h"
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
MutantJumping::MutantJumping()
	:
    m_mutant{},
	m_player{}
{
	// アニメーションを作成する
	m_animation = std::make_unique<MutantJumpingAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantJumping::~MutantJumping()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantJumping::Initialize()
{
	// ミュータントのポインタを取得する
	m_mutant = static_cast<Mutant*>(EventMessenger::ExecuteGetter(GetterList::GetMutant));
	// プレイヤーのポインタを取得する
	m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
	// アニメーションを初期化する
	m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantJumping::Update()
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
void MutantJumping::Render()
{
	// アニメーションを描画する
	m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantJumping::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// 斬りつけの処理
//---------------------------------------------------------
void MutantJumping::Slashing()
{
	using namespace DirectX::SimpleMath;

	// ミュータントがダメージを与えられる状態であれば通過
	if (!m_animation->IsAbleToDealDamage())
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
		// プレイヤーにダメージを与える
		m_player->Damage(1);
	}
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void MutantJumping::TransitionToWalking()
{
	// アニメーションが終了したら待機状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
}