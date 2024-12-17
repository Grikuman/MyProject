/*
	@file	SceneManager.h
	@brief	�V�[���}�l�[�W���N���X
*/
#pragma once
#include "Game/Interface/IScene.h"

class SceneManager
{
public:
	// �R���X�g���N�^
	SceneManager();
	// �f�X�g���N�^
	~SceneManager();
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�悷��
	void Render();
	// �I������
	void Finalize();

private:
	// �V�[����ύX����
	void ChangeScene(IScene::SceneID sceneID);
	// �V�[�����쐬����
	void CreateScene(IScene::SceneID sceneID);
	// �V�[�����폜����
	void DeleteScene();

private:
	std::unique_ptr<IScene> m_currentScene;
};
