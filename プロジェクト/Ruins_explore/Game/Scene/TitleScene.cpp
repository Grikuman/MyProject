/*
	�t�@�C�����FTitleScene.cpp
	�@�@�@�T�v�F�^�C�g���V�[�����Ǘ�����N���X
*/
#include "pch.h"
#include "TitleScene.h"
#include "Framework/DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Framework/Graphics.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_isChangeScene{},
	m_titleSceneUI{}
{
	// �^�C�g��UI�Ǘ��N���X���쐬����
	m_titleSceneUI = std::make_unique<TitleSceneUI>(this);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TitleScene::~TitleScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TitleScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// ����������
	m_titleSceneUI->Initialize();
	// BGM���Đ�
	Audio::GetInstance()->PlayBGM("TitleBGM",0.05f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �^�C�g��UI�Ǘ��N���X���X�V����
	m_titleSceneUI->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{
	m_titleSceneUI->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void TitleScene::Finalize()
{
	m_titleSceneUI->Finalize();
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::MAPSELECT;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

//---------------------------------------------------------
// �V�[���J�ڂ���
//---------------------------------------------------------
void TitleScene::ChangeScene()
{
	m_isChangeScene = true;
}
