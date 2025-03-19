/*
	�t�@�C�����FPlayerWalk.h
	�@�@�@�T�v�F�v���C���[�̕��s��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// �O���錾
class Player;

class PlayerWalk : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerWalk(Player* player);
	// �f�X�g���N�^
	~PlayerWalk() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// �v���C���[�ړ�
	void PlayerMove();
	// ���s����_�b�V����
	void WalkToDash();
	// ���s����U����
	void WalkToAttack();

private:
	// ��]���鑬��
	const float ROTATE_SPEED = 3.0f;

private:
	//�v���C���[
	Player* m_player;
	// �L�[�������Ă��鎞��
	float m_keyHoldTime;
	// �}�E�X�̈ړ��ۑ�
	int m_prevMouse;
};
