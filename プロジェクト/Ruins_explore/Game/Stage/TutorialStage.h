/*
	�t�@�C�����FTutorialStage.h
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"
#include "Game/Stage/StageCollision.h"
#include "Game/Stage/StageDecoration.h"
#include "Game/UI/TutorialGuideUI.h"
#include "Game/Enemy/PracticeEnemy/PracticeEnemy.h"

class TutorialStage final : public IStage
{
public:
	// �X�e�[�W���N���A�������ǂ���
	bool IsEndStage() const override { return m_isEndStage; }

public:
	// �R���X�g���N�^
	TutorialStage(std::string stageName);
	// �R���X�g���N�^
	~TutorialStage() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �Փ˔���
	void Collision();
	// �X�e�[�W�̑J�ڏ���
	void Transition();
	// �`���[�g���A���̃~�b�V��������
	void Mission();

private:
	// �v���C���[
	std::unique_ptr<Player> m_player;
	// �`���[�g���A���K�C�h��UI
	std::unique_ptr<TutorialGuideUI> m_tutorialGuideUI;
	// �`���[�g���A���p�̓G
	std::unique_ptr<PracticeEnemy> m_practiceEnemy;
	// �X�e�[�W�̃��f��
	DirectX::Model* m_stageModel;
	// �X�e�[�W�̖��O
	std::string m_stageName;
	// �X�e�[�W�I���t���O
	bool m_isEndStage;
	// �ړ��J�E���g
	int m_moveCnt;
};
