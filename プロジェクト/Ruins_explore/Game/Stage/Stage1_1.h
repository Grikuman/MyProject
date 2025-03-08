/*
	�t�@�C�����FStage1_1.h
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"
#include "Game/Stage/StageCollision.h"
#include "Game/Stage/StageDecoration.h"

class Stage1_1 final : public IStage
{
public:
	// ���̃X�e�[�WID���擾����
	StageID GetNextStageID() const override { return StageID::NONE; }
	// �X�e�[�W���N���A�������ǂ���
	bool IsClearStage() const override { return m_isClearStage; }

public:
	// �R���X�g���N�^
	Stage1_1(std::string stageName);
	// �R���X�g���N�^
	~Stage1_1() override;
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
	bool m_isClearStage;
	// �Q�[������
	float m_gameTime;
};
