/*
	@file	SmallEnemy.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Game/Enemy/SmallEnemy.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <GeometricPrimitive.h>
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
SmallEnemy::SmallEnemy()
	:
	m_commonResources{},
	m_camera{},
	m_cylinder{},
	m_position{}
{
	m_state = SmallEnemy::STATE::ALIVE;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
SmallEnemy::~SmallEnemy()
{
	
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void SmallEnemy::Initialize(CommonResources* resources, NRLib::TPS_Camera* camera,DirectX::SimpleMath::Vector3 position)
{
	assert(resources);
	m_commonResources = resources;
	m_camera = camera;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	m_cylinder = DirectX::GeometricPrimitive::CreateCylinder(context, 3.f);
	m_position = position;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void SmallEnemy::Update()
{
	
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void SmallEnemy::Render()
{
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	world *= Matrix::CreateTranslation(m_position);
	DirectX::SimpleMath::Matrix view = m_camera->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = m_camera->GetProjectionMatrix();
	if (m_state == SmallEnemy::ALIVE)
	{
		m_cylinder->Draw(world, view, proj, Colors::White);
	}
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void SmallEnemy::Finalize()
{
	// do nothing.
}

void SmallEnemy::SetState(SmallEnemy::STATE state)
{
	m_state = state;
}

DirectX::BoundingSphere SmallEnemy::GetBoundingSphere()
{
	Vector3 center = m_position; // 当たり判定球の中心
	float radius = 0.5f; // 敵のサイズに応じて調整
	return DirectX::BoundingSphere(center, radius);
}
