/*
	�t�@�C�����FPlayerRunning.h
	�@�@�@�T�v�F�v���C���[�̑����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerRunningAnimation.h"

// �O���錾
class Player;

class PlayerRunning : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerRunning(Player* player);
	// �f�X�g���N�^
	~PlayerRunning() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// ���鏈��
	void Running();
	// �ҋ@��Ԃւ̈ڍs����
	void TransitionToIdling();
	// �����Ԃւ̈ڍs����
	void TransitionToRolling();
	// �����̏���
	void Direction();

private:
	// �v���C���[
	Player* m_player;
	// �A�j���[�V����
	std::unique_ptr<PlayerRunningAnimation> m_animation;
};
