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
	~PlayerWalk();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();
private:
	// �v���C���[�ړ�
	void PlayerMove();
	// ���s����_�b�V����
	void WalkToDash();
	// ���s����U����
	void WalkToAttack();
	// ���s����W�����v��
	void WalkToJump();

private:
	//�v���C���[
	Player* m_player;
	// ���f��
	DirectX::Model* m_model;
	// �L�[�������Ă��鎞��
	float m_keyHoldTime;
};
