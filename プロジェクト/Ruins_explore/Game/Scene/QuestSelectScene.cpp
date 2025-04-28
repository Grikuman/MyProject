/*
	�t�@�C�����FQuestSelectScene.cpp
	�@�@�@�T�v�F�N�G�X�g�I���V�[�����Ǘ�����N���X
*/
#include "pch.h"
#include "Game/UI/QuestSelectUI.h"
#include "QuestSelectScene.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
QuestSelectScene::QuestSelectScene()
	:
	m_isChangeScene{}
{
	// �N�G�X�g�I����UI���쐬����
	m_questSelectUI = std::make_unique<QuestSelectUI>();
	// �X�e�[�W�J�n�̉��o���쐬����
	m_stageStart = std::make_unique<StageStart>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
QuestSelectScene::~QuestSelectScene()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void QuestSelectScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// �N�G�X�g�I����UI������������
	m_questSelectUI->Initialize();
	// �N�G�X�g�J�n�̉��o������������
	m_stageStart->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void QuestSelectScene::Update(float elapsedTime)
{
	// �N�G�X�g�J�n�̉��o
	if (m_questSelectUI->GetQuestStart())
	{
		// �X�e�[�W�J�n���o���X�V����
		m_stageStart->Update();
		// ���o���I��������
		if (m_stageStart->GetEnd())
		{
			// �v���C�V�[���Ɉڍs
			ChangeScene();
		}
	}
	// �N�G�X�g�J�n�̉��o�ł͂Ȃ��Ƃ�
	else
	{
		// �N�G�X�g�I����UI���X�V����
		m_questSelectUI->Update();
	}

	// ���̃V�[��ID���擾����
	GetNextSceneID();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void QuestSelectScene::Render()
{
	// �N�G�X�g�I����ʂ�UI��`�悷��
	m_questSelectUI->Render();
	// �N�G�X�g�J�n�̉��o��`�悷��
	m_stageStart->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void QuestSelectScene::Finalize()
{
	// �N�G�X�g�I����ʂ�UI�̏I������
	m_questSelectUI->Finalize();
	// �N�G�X�g�J�n�̉��o�̏I������
	m_stageStart->Finalize();
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID QuestSelectScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}
	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
