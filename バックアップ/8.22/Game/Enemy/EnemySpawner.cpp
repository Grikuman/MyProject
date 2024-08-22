/*
	@file	EnemySpawner.cpp
	@brief	��ʓI�ȃV�[���N���X

	//�G�̍\�z��

�̂܂� - �̂��g���čU������B
�͂�܂� - �����œ������B
�ق̂��܂� - �΂�f���čU������B
�݂��܂� - �����g���čU������B
�����܂� - �����g���čU������B
����܂� - ��𓊂�����A�̓����肵�čU������B
�ł�܂� - �d�C���g���čU������B
�����܂� - �e�ɉB��Ċ�P�U��������B
�܂�܂� - �̂��ۂ߂č����œ]����Ȃ���U������B
���܂� - ��ɋ����A�ł𑀂�B
���Ă܂� - �傫�ȏ��������Ėh�䂷��B
�΂��܂� - ���������A�󒆂���U������B
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
// �R���X�g���N�^
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
	// ��������G�l�~�[���𐶑��m�F�p�ϐ��ɐݒ肷��
	m_aliveEnemy = MAX_TUNOMARU;
	// �e�G�l�~�[�𐶐�����
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// �̂܂�𐶐�����
		m_tunomaru[i] = std::make_unique<Tunomaru>();
	}
	// �G�̏����ʒu��ݒ肷��
	m_tunomaru[0]->Initialize(m_commonResources,Vector3(2.f, 0.f, -5.f));
	m_tunomaru[1]->Initialize(m_commonResources,Vector3(-2.f, 0.f, -5.f));
	// �����蔻��
	m_collision = std::make_unique<Collision>();

	// �V�[���J�ڃt���O��������
	m_isChangeScene = false;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void EnemySpawner::Update(DirectX::BoundingSphere boundingSphere, bool isPlayerAttack)
{
	m_aliveEnemy = MAX_ENEMY;
	// �̂܂�̏���
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// �e�̂܂���X�V
		m_tunomaru[i]->Update();
		// ����:�̂܂�ƃv���C���[���������Ă���@���@�v���C���[���U�����Ă���
		if (m_collision->SphereIntersects(boundingSphere, m_tunomaru[i]->GetBoundingSphere()) && isPlayerAttack)
		{
			// �̂܂�Ƀ_���[�W����
			m_tunomaru[i]->Hit(0.5f);
		}
		// �̂܂邪���S���Ă��邩���肷��
		if (m_tunomaru[i]->GetState() == Tunomaru::STATE::DEAD)
		{
			// �������Ă���G�̐������炷
			m_aliveEnemy--;
		}
	}
	// �G���S�����ꂽ��V�[���J�ڃt���O��ON
	if (m_aliveEnemy <= 0.f)
	{
		m_isChangeScene = true;
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
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// �̂܂��`��
		m_tunomaru[i]->Render(view,proj);
	}
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void EnemySpawner::Finalize()
{
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		m_tunomaru[i]->Finalize();
	}
}

// �V�[���J�ڂ��邩�ǂ����擾����
bool EnemySpawner::IsChangeScene()
{
	if (m_isChangeScene)
	{
		return true;
	}
	return false;
}
