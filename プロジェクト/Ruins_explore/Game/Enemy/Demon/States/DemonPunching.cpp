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
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
DemonPunching::DemonPunching()
	:
    m_demon{}
{
	// アニメーションを作成する
	m_animation = std::make_unique<DemonPunchingAnimation>();
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
	// デーモンのポインタを取得する
	m_demon = static_cast<Demon*>(EventMessenger::ExecuteGetter(GetterList::GetDemon));
	// プレイヤーのポインタを取得する
	m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
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

	// プレイヤーの位置を取得する
	Vector3 playerPos = m_player->GetPosition();
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
	Vector3 toPlayer = m_player->GetPosition() - m_demon->GetPosition();
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
void DemonPunching::TransitionToWalking()
{
	// アニメーションが終了したら待機状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		m_demon->ChangeState(m_demon->GetDemonWalking());
	}
}