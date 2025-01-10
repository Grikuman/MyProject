/*
	�t�@�C�����FPlayerJump.h
	�@�@�@�T�v�F�v���C���[�̃W�����v��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// �O���錾
class Player;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerJump : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerJump(Player* player);
	// �f�X�g���N�^
	~PlayerJump();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �W�����v����
	void Jump();
	// �ړ�����
	void Move();
	// �W�����v������s��
	void JumpToWalk();

private:
	// �W�����v���s������
	const float JUMP_TIME = 10;

private:
	//�v���C���[
	Player* m_player;
	
	// �W�����v����
	float m_jumpTime; 
};
