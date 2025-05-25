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
	// ジャンプの処理
	Jumping();
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
// ジャンプの処理
//---------------------------------------------------------
void MutantJumping::Jumping()
{
	using namespace DirectX::SimpleMath;

	// ジャンプ前のプレイヤーの位置を取得する
	Vector3 playerPos = m_mutant->GetJumpPlayerPos();
	// ミュータントの位置を取得する
	Vector3 mutantPos = m_mutant->GetPosition();

	// プレイヤーへの方向を計算する
	Vector3 directionToPlayer = playerPos - mutantPos;
	directionToPlayer.Normalize(); // 正規化して方向ベクトルにする
	// ミュータントの回転をプレイヤーに向ける
	float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
	m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

	// 速度を設定する
	m_mutant->AddVelocity(directionToPlayer);
	m_mutant->ApplyVelocity(APPLY_VELOCITY);
	// 位置を設定する
	m_mutant->SetPosition(mutantPos + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void MutantJumping::TransitionToWalking()
{
	// アニメーションが終了したら歩き状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		// 歩き状態へ移行する
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
}
