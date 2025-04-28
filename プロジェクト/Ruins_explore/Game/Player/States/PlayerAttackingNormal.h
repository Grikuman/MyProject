/*
	�t�@�C�����FPlayerAttackingNormal.h
	�@�@�@�T�v�F�v���C���[�̒ʏ�U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerAttackingNormalAnimation.h"

// �O���錾
class Player;

class PlayerAttackingNormal : public IPlayerState
{
public:
	// �U���͈͂��擾����
	DirectX::BoundingSphere GetAttackRange();

public:
	// �R���X�g���N�^
	PlayerAttackingNormal(Player* player);
	// �f�X�g���N�^
	~PlayerAttackingNormal() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �ҋ@��Ԃւ̈ڍs����
	void TransitionToIdling();

private:
	// �U���̋���
	const float ATTACK_DISTANCE = 3.0f;

private:
	//�v���C���[
	Player* m_player;
	// �A�j���[�V����
	std::unique_ptr<PlayerAttackingNormalAnimation> m_animation;
};
