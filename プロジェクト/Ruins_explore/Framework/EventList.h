/*
	�t�@�C�����FEventList.h
	�@�@�@�T�v�F�C�x���g�̎��
*/
#pragma once

enum class EventList
{
	// �{�X���v���C���[�ɍU�����Ă��邩
	PlayerCanDamageBoss,
};

//---------------------------------------------------------
//�O���t�B�b�N�X�̃C���X�^���X���擾
//---------------------------------------------------------
enum class GetterList
{
	// �v���C���[�̃|�C���^���擾����
	GetPlayer,
	// �{�X�̃|�C���^���擾����
	GetBoss,
	// ���̃|�C���^���擾����
	GetSword,
	// ���_�̃|�C���^���擾����
	GetCudgel,
	// �J�����̃^�[�Q�b�g�̍��W���擾����
	GetTargetPosition,
};