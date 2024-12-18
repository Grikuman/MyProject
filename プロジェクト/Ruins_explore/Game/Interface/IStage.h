/*
	@file	IStageBase.h
	@brief	�X�e�[�W�̃C���^�[�t�F�[�X
*/
#pragma once

class IStage
{
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
