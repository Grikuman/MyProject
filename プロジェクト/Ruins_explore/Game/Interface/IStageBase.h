/*
	@file	IStageBase.h
	@brief	�X�e�[�W�̃C���^�[�t�F�[�X
*/
#pragma once

class IStageBase
{
public:
	virtual ~IStageBase() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};
