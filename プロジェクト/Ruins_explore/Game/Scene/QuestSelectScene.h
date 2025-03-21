/*
	�t�@�C�����FQuestSelectScene.h
	�@�@�@�T�v�F�N�G�X�g�I���V�[�����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Transition/StageStart.h"

class QuestSelectUI;

class QuestSelectScene final : public IScene
{
public:
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;

public:
	// �V�[����ύX����
	void ChangeScene();

public:
	// �R���X�g���N�^
	QuestSelectScene();
	// �f�X�g���N�^
	~QuestSelectScene() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �N�G�X�g�I����UI
	std::unique_ptr<QuestSelectUI> m_questSelectUI;
	// �N�G�X�g�J�n�̉��o
	std::unique_ptr<StageStart> m_stageStart;
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
};
