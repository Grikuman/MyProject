/*
	�t�@�C�����FPlayScene.h
	�@�@�@�T�v�F�v���C�V�[�����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Interface/IStage.h"
#include "Game/Transition/StageEnd.h"

class PlayScene final : public IScene
{
public:
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;

public:
	// �R���X�g���N�^
	PlayScene();
	// �R���X�g���N�^
	~PlayScene() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �X�e�[�W�̏�����
	void StageInitialize();

private:
	// ���݂̃X�e�[�W
	std::unique_ptr<IStage> m_currentStage;
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	// �X�e�[�W�I�����o
	std::unique_ptr<StageEnd> m_stageEnd;
};
