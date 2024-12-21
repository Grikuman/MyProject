/*
	�t�@�C�����FIPlayerPart.h
	�@�@�@�T�v�F�v���C���[�̃p�[�c�̃C���^�[�t�F�[�X
*/
#pragma once

class IPlayerPart
{
public:
	// �f�X�g���N�^
	virtual ~IPlayerPart() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};
