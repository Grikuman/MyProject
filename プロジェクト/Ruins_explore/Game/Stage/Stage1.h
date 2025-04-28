/*
	�t�@�C�����FStage1.h
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"
#include "Game/Stage/StageCollision.h"
#include "Game/Stage/StageDecoration.h"

class Stage1 final : public IStage
{
public:
	// �X�e�[�W���N���A�������ǂ���
	bool IsEndStage() const override { return m_isEndStage; }

public:
	// �R���X�g���N�^
	Stage1(std::string stageName);
	// �R���X�g���N�^
	~Stage1() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �X�e�[�W�̑J�ڏ���
	void Transition();

private:
	// �Q�[���̐�������
	static const int MAX_GAMETIME = 60;
	// BGM�̉���
	const float BGM_VOLUME = 0.07f;

private:
	// �X�e�[�W�̓G
	std::unique_ptr<StageEnemy> m_stageEnemy;
	// �X�e�[�W�̏Փ˔���
	std::unique_ptr<StageCollision> m_stageCollision;
	// �X�e�[�W�̑����I�u�W�F�N�g
	std::unique_ptr<StageDecoration> m_stageDecoration;
	// �v���C���[
	std::unique_ptr<Player> m_player;
	//����UI
	std::unique_ptr<TimeUI> m_timeUI;
	// �X�e�[�W�̖��O
	std::string m_stageName;
	// �X�e�[�W�N���A�t���O
	bool m_isEndStage;
	// �Q�[������
	float m_gameTime;
};
