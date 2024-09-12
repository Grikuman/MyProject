/*
	�t�@�C��: EnemySpawner.cpp
	�N���X  : �G�����N���X

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
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
EnemySpawner::EnemySpawner(Player* player)
	:
	m_commonResources{},
	m_player{player},
	m_aliveEnemy{},
	m_tunomaru{},
	m_rockBoss{},
	m_isChangeScene{}
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
void EnemySpawner::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	// ��������G�l�~�[���𐶑��m�F�p�ϐ��ɐݒ肷��
	m_aliveEnemy = MAX_TUNOMARU + 1;
	//------------------------------------------------------------------
	// * �e�G�l�~�[�𐶐����� *
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// �̂܂�
		m_tunomaru[i] = std::make_unique<Tunomaru>(m_player);
	}
	// ��{�X
	m_rockBoss = std::make_unique<RockBoss>(m_player);

	//------------------------------------------------------------------
	// * �G�̏����ʒu��ݒ肷�� *
	// �̂܂�
	m_tunomaru[0]->Initialize(resources,Vector3(2.f, 1.f, -8.f));
	m_tunomaru[1]->Initialize(resources,Vector3(-2.f, 1.f, -8.f));
	// ��{�X
	m_rockBoss->Initialize(resources, Vector3(0.f, 0.f, -10.f));

	// �V�[���J�ڃt���O��������
	m_isChangeScene = false;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void EnemySpawner::Update()
{
	m_aliveEnemy = MAX_ENEMY;

	// �̂܂�̏���
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// �e�̂܂���X�V
		m_tunomaru[i]->Update();
		
		// �̂܂邪���S���Ă���ꍇ��
		if (m_tunomaru[i]->GetIsAlive() == false)
		{
			// �������Ă���G�̐������炷
			m_aliveEnemy--;
		}
	}

	// ��{�X���X�V����
	m_rockBoss->Update();
	
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
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// �̂܂��`��
		m_tunomaru[i]->Render();
	}
	// ��{�X��`��
	m_rockBoss->Render();
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
	m_rockBoss->Finalize();
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
