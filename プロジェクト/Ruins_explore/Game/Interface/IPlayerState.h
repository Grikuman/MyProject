/*
	�t�@�C�����FIPlayerState.h
	�@�@�@�T�v�F�v���C���[�̏�Ԃ̃C���^�[�t�F�[�X
*/
#pragma once

class IPlayerState
{
public:
	// �f�X�g���N�^
	virtual ~IPlayerState() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};
