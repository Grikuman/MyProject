/*
	@file	EnemySpawner.cpp
	@brief	一般的なシーンクラス

	//敵の構想案

つのまる - つのを使って攻撃する。
はやまる - 高速で動き回る。
ほのおまる - 火を吐いて攻撃する。
みずまる - 水を使って攻撃する。
かぜまる - 風を使って攻撃する。
いわまる - 岩を投げたり、体当たりして攻撃する。
でんまる - 電気を使って攻撃する。
かげまる - 影に隠れて奇襲攻撃をする。
まるまる - 体を丸めて高速で転がりながら攻撃する。
よるまる - 夜に強く、闇を操る。
たてまる - 大きな盾を持って防御する。
つばさまる - 翼を持ち、空中から攻撃する。
*/
#include "pch.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <GeometricPrimitive.h>
#include "Libraries/NRLib/TPS_Camera.h"
#include "Game/Enemy/Tunomaru.h"
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemySpawner::EnemySpawner(Player* player)
	:
	m_commonResources{},
	m_player{player},
	m_aliveEnemy{},
	m_tunomaru{},
	m_collision{},
	m_isChangeScene{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
EnemySpawner::~EnemySpawner()
{
	
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void EnemySpawner::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	// 生成するエネミー数を生存確認用変数に設定する
	m_aliveEnemy = MAX_TUNOMARU;
	// 各エネミーを生成する
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// つのまるを生成する
		m_tunomaru[i] = std::make_unique<Tunomaru>(m_player);
	}
	// 敵の初期位置を設定する
	m_tunomaru[0]->Initialize(m_commonResources,Vector3(2.f, 1.f, -8.f));
	m_tunomaru[1]->Initialize(m_commonResources,Vector3(-2.f, 1.f, -8.f));
	// 当たり判定
	m_collision = std::make_unique<Collision>();

	// シーン遷移フラグを初期化
	m_isChangeScene = false;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemySpawner::Update(DirectX::BoundingSphere boundingSphere, bool isPlayerAttack)
{
	m_aliveEnemy = MAX_ENEMY;
	// つのまるの処理
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// 各つのまるを更新
		m_tunomaru[i]->Update();
		// 条件:つのまるとプレイヤーが当たっている　かつ　プレイヤーが攻撃している場合
		if (m_collision->SphereIntersects(boundingSphere, m_tunomaru[i]->GetBoundingSphere()) && isPlayerAttack)
		{
			// つのまるにダメージ処理
			m_tunomaru[i]->SetHP(m_tunomaru[i]->GetHP() - 0.5f);
			m_tunomaru[i]->SetHit(true);
		}
		// つのまるが死亡している場合は
		if (m_tunomaru[i]->GetIsAlive() == false)
		{
			// 生存している敵の数を減らす
			m_aliveEnemy--;
		}
	}
	// 敵が全員やられたらシーン遷移フラグをON
	if (m_aliveEnemy <= 0.f)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemySpawner::Render()
{
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// つのまるを描画
		m_tunomaru[i]->Render();
	}
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void EnemySpawner::Finalize()
{
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		m_tunomaru[i]->Finalize();
	}
}

// シーン遷移するかどうか取得する
bool EnemySpawner::IsChangeScene()
{
	if (m_isChangeScene)
	{
		return true;
	}
	return false;
}
