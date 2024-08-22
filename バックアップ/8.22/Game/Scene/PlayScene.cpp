/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"
#include <iostream>
#include "WorkTool/Collision.h"

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
	m_enemySpawner{},
	m_textUI{},
	m_gameTime{}
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

	// �v���C���[���쐬
	m_player = std::make_unique<Player>();
	m_player->Initialize(m_commonResources);
	// �V�����쐬
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize(m_commonResources);
	// �t�B�[���h���쐬
	m_field = std::make_unique<Field>();
	m_field->Initialize(m_commonResources, m_player->GetCamera());
	// �G�l�~�[�X�|�i�[���쐬
	m_enemySpawner = std::make_unique<EnemySpawner>();
	m_enemySpawner->Initialize(m_commonResources, m_player->GetCamera());
	//TextUI���쐬
	m_textUI = std::make_unique<TextUI>(
		m_commonResources->GetDeviceResources()->GetD3DDevice(),
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		);

	// �Q�[�����Ԃ�ݒ�
	m_gameTime = MAX_GAMETIME;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	
	//�Q�[������
	m_gameTime -= elapsedTime;

	//�v���C���[���X�V
	m_player->Update(elapsedTime);
	// �V�����X�V
	m_sky->Update();
	// �t�B�[���h���X�V
	m_field->Update();
	// �G�l�~�[�X�|�i�[���X�V
	m_enemySpawner->Update(m_player->GetBoundingSphere(), m_player->GetIsAttack());
	// TextUI���X�V
	m_textUI->Update(m_gameTime);
	// �G���S�����񂾂�V�[���J�ڂ��s��
	if (m_enemySpawner->IsChangeScene())
	{
		m_isChangeScene = true;
	}
	// ���̃V�[��ID���擾����
	GetNextSceneID();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	// �v���C���[��`��
	m_player->Render();
	// �V����`��
	//m_sky->Render();
	// �t�B�[���h��`��
	m_field->Render();
	// �G�l�~�[�X�|�i�[��`��
	m_enemySpawner->Render();
	//TextUI��`��
	m_textUI->Render();
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
	m_textUI->Finalize();
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
