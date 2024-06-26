/*
	@file	SmallEnemy.cpp
	@brief	��ʓI�ȃV�[���N���X
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
// �R���X�g���N�^
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
// �f�X�g���N�^
//---------------------------------------------------------
SmallEnemy::~SmallEnemy()
{
	
}

//---------------------------------------------------------
// ����������
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
// �X�V����
//---------------------------------------------------------
void SmallEnemy::Update()
{
	
}

//---------------------------------------------------------
// �`�悷��
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
// ��n������
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
	Vector3 center = m_position; // �����蔻�苅�̒��S
	float radius = 0.5f; // �G�̃T�C�Y�ɉ����Ē���
	return DirectX::BoundingSphere(center, radius);
}
