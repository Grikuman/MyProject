/*
	�t�@�C�����FIStage.h
	�@�@�@�T�v�F�X�e�[�W�̃C���^�[�t�F�[�X
*/
#pragma once

// �X�e�[�WID
enum class StageID
{
	NONE,
	TutorialStage,
	Stage1,
};

class IStage
{
public:
	// �X�e�[�W���I���������ǂ���
	virtual bool IsEndStage() const = 0;

public:
	virtual ~IStage() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};
