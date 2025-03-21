/*
	�t�@�C�����FPlayScene.cpp
	�@�@�@�T�v�F�v���C�V�[�����Ǘ�����N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "Framework/Data.h"
#include "Framework/Graphics.h"
#include "Libraries/Microsoft/ReadData.h"
#include "Libraries/Microsoft/RenderTexture.h"

#include "ScreenGrab.h"
#include "wincodec.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_currentStage{},
	m_stageEnd{}
{
	// �X�e�[�W�I�����o���쐬����
	m_stageEnd = std::make_unique<StageEnd>();
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
	// �X�e�[�W�̏�����
	StageInitialize();
	// �X�e�[�W�I�����o������������
	m_stageEnd->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	// �����X�e�[�W���I�������牉�o���X�V����
	if (m_currentStage->IsEndStage()) 
	{
		// ���o���Đ�
		m_stageEnd->Update();
		// ���o���I��������
		if (m_stageEnd->GetEnd())
		{
			// ���U���g�ֈڍs
			m_isChangeScene = true;
		}
	}
	else // �X�e�[�W���I������܂�
	{
		// ���݂̃X�e�[�W���X�V����
		m_currentStage->Update(elapsedTime);
	}

	// ���̃V�[��ID���擾����
	GetNextSceneID();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	// �X�e�[�W��`�悷��
	m_currentStage->Render();
	// �X�e�[�W�̏I�����o��`�悷��
	m_stageEnd->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// �X�e�[�W�̏I������
	m_currentStage->Finalize();
}

//---------------------------------------------------------
// �X�e�[�W�̏�����
//---------------------------------------------------------
void PlayScene::StageInitialize()
{
	// �I������X�e�[�W�p�̕ϐ�
	StageID selectStage = StageID::TutorialStage;

	// �}�b�v�I���őI�΂ꂽ�X�e�[�W���m�F����
	switch (Data::GetInstance()->GetMapSelectStage())
	{
	case 0:
		selectStage = StageID::TutorialStage;
		break;
	case 1:
		selectStage = StageID::Stage1;
		break;
	default:
		break;
	}

	// �}�b�v�I���őI�΂ꂽ�X�e�[�W�𐶐�����
	m_currentStage = StageFactory::CreateStage(selectStage);

	// �X�e�[�W������������
	m_currentStage->Initialize(); 
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



