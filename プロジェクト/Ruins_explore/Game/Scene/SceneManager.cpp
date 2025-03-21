/*
	�t�@�C�����FSceneManager.cpp
	�@�@�@�T�v�F�V�[���S�̂��Ǘ�����N���X
*/
#include "pch.h"
#include "SceneManager.h"
//---------------------------
#include "PlayScene.h"
#include "TitleScene.h"
#include "QuestSelectScene.h"
#include "ResultScene.h"
//---------------------------
#include "Game/Screen.h"
#include"Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/InputDevice.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <iostream>


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_fade{}
{
	// �t�F�[�h���쐬����
	m_fade = std::make_unique<Fade>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SceneManager::~SceneManager()
{
	Finalize();
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void SceneManager::Initialize()
{
	// �����V�[����ݒ�
	ChangeScene(IScene::SceneID::TITLE);
	// �t�F�[�h������������
	m_fade->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	// �V�[�����X�V����
	m_currentScene->Update(elapsedTime);
	// �t�F�[�h���X�V����
	m_fade->Update();
	// �����p�ϐ��F���̃V�[��
	const IScene::SceneID nextSceneID = m_currentScene->GetNextSceneID();
	// �V�[����ύX���Ȃ��Ƃ�
	if (nextSceneID == IScene::SceneID::NONE) return;
	// �V�[����ύX����Ƃ�
	ChangeScene(nextSceneID);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SceneManager::Render()
{
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::Identity;

	// �V�[����`�悷��
	m_currentScene->Render();
	// �t�F�[�h��`�悷��
	m_fade->Render(view, proj);
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void SceneManager::Finalize()
{
	DeleteScene();
	m_fade->Finalize();
}

//---------------------------------------------------------
// �V�[����ύX����
//---------------------------------------------------------
void SceneManager::ChangeScene(IScene::SceneID sceneID)
{
	m_fade->FadeIn();
	DeleteScene();
	m_fade->FadeOut();
	CreateScene(sceneID);
}

//---------------------------------------------------------
// �V�[�����쐬����
//---------------------------------------------------------
void SceneManager::CreateScene(IScene::SceneID sceneID)
{
	assert(m_currentScene == nullptr);

	switch (sceneID)
	{
		case IScene::SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>();
			break;
		case IScene::SceneID::MAPSELECT:
			m_currentScene = std::make_unique<QuestSelectScene>();
			break;
		case IScene::SceneID::PLAY:
			m_currentScene = std::make_unique<PlayScene>();
			break;
		case IScene::SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
	}

	assert(m_currentScene && "SceneManager::CreateScene::���̃V�[������������܂���ł����I");
	m_currentScene->Initialize();
}

//---------------------------------------------------------
// �V�[�����폜����
//---------------------------------------------------------
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}
