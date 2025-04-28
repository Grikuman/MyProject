/*
	�t�@�C�����FResultScene.cpp
	�@�@�@�T�v�F���U���g�V�[�����Ǘ�����N���X
*/
#include "pch.h"
#include "ResultScene.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_isChangeScene{},
	m_resultSceneUI{}
{
	// UI���쐬����
	m_resultSceneUI = std::make_unique<ResultSceneUI>(this);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
ResultScene::~ResultScene()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ResultScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// UI������������
	m_resultSceneUI->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	// �L�[�{�[�h���擾����
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

	// �X�y�[�X�L�[����������V�[���J��
	if (kb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}

	// UI���X�V����
	m_resultSceneUI->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ResultScene::Render()
{
	// UI��`�悷��
	m_resultSceneUI->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ResultScene::Finalize()
{

}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

