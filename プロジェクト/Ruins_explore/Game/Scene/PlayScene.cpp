/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "WorkTool/Data.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_currentStage{}
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
void PlayScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	// �I�������X�e�[�W
	StageID selectStage = StageID::Stage1_1;

	// �I�������X�e�[�W�𐶐�����
	m_currentStage = StageFactory::CreateStage(selectStage);
	m_currentStage->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	m_currentStage->Update(elapsedTime);

	// �X�e�[�W���N���A�����玟�̃X�e�[�W�֐i��
	if (m_currentStage->IsClearStage()) 
	{
		TransitionToNextStage();
	}

	// ���̃V�[��ID���擾����
	GetNextSceneID();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	m_currentStage->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	m_currentStage->Finalize();
}

//---------------------------------------------------------
// ���̃X�e�[�W�ւ̈ڍs����������
//---------------------------------------------------------
void PlayScene::TransitionToNextStage()
{
	// ���݂̃X�e�[�W�̏I������
	m_currentStage->Finalize();

	// ���̃X�e�[�WID���擾
	StageID nextStageID = m_currentStage->GetNextStageID();

	// ���̃X�e�[�W�𐶐�
	if (nextStageID != StageID::NONE)
	{
		m_currentStage = StageFactory::CreateStage(nextStageID);
		m_currentStage->Initialize();
	}
	else {
		// �S�X�e�[�W�I����A�V�[���ύX�t���O��ݒ�
		m_isChangeScene = true;
	}
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
