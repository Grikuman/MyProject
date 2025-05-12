/*
	�t�@�C�����FPlayerIdling.h
	�@�@�@�T�v�F�v���C���[�̑ҋ@��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerIdlingAnimation.h"

// �O���錾
class Player;

class PlayerIdling : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerIdling();
	// �f�X�g���N�^
	~PlayerIdling() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �ҋ@����
	void Idling();
	// �����Ԃւ̈ڍs����
	void TransitionToRunning();
	// �ʏ�U����Ԃւ̈ڍs����
	void TransitionToAttackingNormal();

private:
	//�v���C���[
	Player* m_player;
	// �A�j���[�V����
	std::unique_ptr<PlayerIdlingAnimation> m_animation;
};
