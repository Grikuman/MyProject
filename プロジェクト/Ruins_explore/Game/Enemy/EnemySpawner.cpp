/*
	@file	EnemySpawner.cpp
	@brief	��ʓI�ȃV�[���N���X
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

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
EnemySpawner::EnemySpawner()
	:
	m_commonResources{},
	m_camera{},
	m_smallEnemy{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
EnemySpawner::~EnemySpawner()
{
	
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void EnemySpawner::Initialize(CommonResources* resources, NRLib::TPS_Camera* camera)
{
	assert(resources);
	m_commonResources = resources;
	m_camera = camera;
	// �e�G�l�~�[�𐶐�����
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i] = std::make_unique<SmallEnemy>();
	}
	m_smallEnemy[0]->Initialize(m_commonResources,m_camera,Vector3(2.f, 0.f, 0.f));
	m_smallEnemy[1]->Initialize(m_commonResources,m_camera,Vector3(-2.f, 0.f, 0.f));
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void EnemySpawner::Update()
{
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i]->Update();
	}
}

//---------------------------------------------------------
// �`�悷��
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
// ��n������
//---------------------------------------------------------
void EnemySpawner::Finalize()
{
	for (int i = 0; i < MAX_SMALL_ENEMY; i++)
	{
		m_smallEnemy[i]->Finalize();
	}
}
