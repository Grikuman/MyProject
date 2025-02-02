/*
	�t�@�C�����FSceneManager.h
	�@�@�@�T�v�F�V�[���S�̂��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Transition/Fade.h"

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
	// ���݂̃V�[��
	std::unique_ptr<IScene> m_currentScene;
	// �t�F�[�h
	std::unique_ptr<Fade> m_fade;
};
