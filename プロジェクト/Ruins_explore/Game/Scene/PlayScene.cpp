/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"
#include <iostream>
#include "Game/Stage/Sky.h"
#include "Game/Stage/Field.h"
#include "Game/Enemy/EnemySpawner.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_commonResources{},
	m_isChangeScene{},
	m_player{},
	m_sky{},
	m_field{},
	m_enemySpawner{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	// �v���C���[�𐶐�
	m_player = std::make_unique<Player>();
	m_player->Initialize(m_commonResources);
	// �V���𐶐�
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize(m_commonResources);
	// �t�B�[���h�𐶐�
	m_field = std::make_unique<Field>();
	m_field->Initialize(m_commonResources);
	// Body����J�������擾���Đݒ肷��
	NRLib::TPS_Camera* playerCamera = m_player->GetCamera();
	if (playerCamera)
	{
		m_field->SetCamera(playerCamera);
	}
	// �G�l�~�[�X�|�i�[�𐶐�
	m_enemySpawner = std::make_unique<EnemySpawner>();
	m_enemySpawner->Initialize(m_commonResources,playerCamera);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//�v���C���[���X�V
	m_player->Update(elapsedTime);
	
	m_sky->Update();
	m_field->Update();
	m_enemySpawner->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	//�v���C���[��`��
	m_player->Render();
	m_sky->Render();
	m_field->Render();
	m_enemySpawner->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	m_player->Finalize();
	m_sky->Finalize();
	m_field->Finalize();
	m_enemySpawner->Finalize();
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
