/*
	�t�@�C�����FStage1_2.h
	�@�@�@�T�v�F�X�e�[�W1_2���Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"

#include "Game/StageObject/Sky.h"
#include "Game/StageObject/Field.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"

namespace NRLib
{
	class FixedCamera;
};

class Stage1_2 final : public IStage
{
public:
	// ���̃X�e�[�WID���擾����
	StageID GetNextStageID() const override { return StageID::NONE; }
	// �X�e�[�W���N���A�������ǂ���
	bool IsClearStage() const override { return m_isClearStage; }
public:
	// �R���X�g���N�^
	Stage1_2(std::string stageName);
	// �R���X�g���N�^
	~Stage1_2() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �Q�[���̐�������
	static const int MAX_GAMETIME = 60;

private:
	// �G�l�~�[
	std::unique_ptr<StageEnemy> m_stageEnemy;
	// �X�e�[�W�̖��O
	std::string m_stageName;
	// �v���C���[
	std::unique_ptr<Player> m_player;
	// �V��
	std::unique_ptr<Sky> m_sky;
	// �t�B�[���h
	std::unique_ptr<Field> m_field;
	//TextUI
	std::unique_ptr<TimeUI> m_timeUI;
	// �v���C�V�[��UI

	// �X�e�[�W�N���A�t���O
	bool m_isClearStage;
	// �Q�[������
	float m_gameTime;
};
