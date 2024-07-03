/*
	@file	EnemySpawner.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Game/Enemy/EnemySpawner.h"
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
EnemySpawner::EnemySpawner()
	:
	m_commonResources{},
	m_camera{},
	m_aliveEnemy{},
	m_tunomaru{},
	m_collision{}
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
void EnemySpawner::Initialize(CommonResources* resources, NRLib::TPS_Camera* camera)
{
	assert(resources);
	m_commonResources = resources;
	m_camera = camera;
	// 生成するエネミー数を生存確認用変数に設定する
	m_aliveEnemy = MAX_TUNOMARU;
	// 各エネミーを生成する
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// つのまるを生成する
		m_tunomaru[i] = std::make_unique<Tunomaru>();
	}
	// 敵の初期位置を設定する
	m_tunomaru[0]->Initialize(m_commonResources,m_camera,Vector3(2.f, 0.f, -5.f));
	m_tunomaru[1]->Initialize(m_commonResources,m_camera,Vector3(-2.f, 0.f, -5.f));
	// 当たり判定
	m_collision = std::make_unique<Collision>();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemySpawner::Update(DirectX::BoundingSphere boundingSphere,bool isPlayerAttack)
{
	// つのまるの処理
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// 各つのまるを更新
		m_tunomaru[i]->Update();
		// 条件:つのまるとプレイヤーが当たっている　かつ　プレイヤーが攻撃している
		if (m_collision->SphereIntersects(boundingSphere, m_tunomaru[i]->GetBoundingSphere()) && isPlayerAttack)
		{
			// つのまるにダメージ処理
			m_tunomaru[i]->Hit(0.5f);
		}
		// つのまるが死亡しているか判定する
		if (m_tunomaru[i]->GetState() == Tunomaru::STATE::DEAD)
		{
			// 生存している敵の数を減らす
			m_aliveEnemy--;
		}
	}

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemySpawner::Render()
{
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	DirectX::SimpleMath::Matrix view = m_camera->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = m_camera->GetProjectionMatrix();
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
