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
#include "Game/Enemy/SmallEnemy.h"
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
	m_smallEnemy{},
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
	// 各エネミーを生成する
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i] = std::make_unique<SmallEnemy>();
	}
	m_smallEnemy[0]->Initialize(m_commonResources,m_camera,Vector3(2.f, 0.f, -5.f));
	m_smallEnemy[1]->Initialize(m_commonResources,m_camera,Vector3(-2.f, 0.f, -5.f));

	m_collision = std::make_unique<Collision>();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemySpawner::Update(DirectX::BoundingSphere boundingSphere,bool isAttack)
{
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i]->Update();
		if (m_collision->CheckCollision(boundingSphere, m_smallEnemy[i]->GetBoundingSphere()) && isAttack == true)
		{
			m_smallEnemy[i]->Hit(0.5f);
		}
	}
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		if (m_smallEnemy[i]->GetState() == SmallEnemy::STATE::DEAD)
		{
			
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
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i]->Render();
	}
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void EnemySpawner::Finalize()
{
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i]->Finalize();
	}
}
