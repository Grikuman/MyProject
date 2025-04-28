/*
	�t�@�C�����FPlayerRolling.h
	�@�@�@�T�v�F�v���C���[�̉����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerRollingAnimation.h"

// �O���錾
class Player;

class PlayerRolling : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerRolling(Player* player);
	// �f�X�g���N�^
	~PlayerRolling() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �������
	void Rolling();
	// �ҋ@��Ԃւ̈ڍs����
	void TransitionToIdling();

private:
	// ���x�̕␳
	const float APPLY_VELOCITY = 0.1f;

private:
	//�v���C���[
	Player* m_player;
	// �A�j���[�V����
	std::unique_ptr<PlayerRollingAnimation> m_animation;
};
