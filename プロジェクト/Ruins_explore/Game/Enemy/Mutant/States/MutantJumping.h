/*
	�t�@�C�����FMutantJumping.h
	�@�@�@�T�v�F�~���[�^���g�̃W�����v��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantJumpingAnimation.h"

// �O���錾
class Mutant;
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class MutantJumping : public IEnemyState
{
public:
	// �R���X�g���N�^
	MutantJumping();
	// �f�X�g���N�^
	~MutantJumping() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �_���[�W����
	void Damage();
	// �W�����v�̏���
	void Jumping();
	// ������Ԃւ̈ڍs����
	void TransitionToWalking();

private:
	// �U���̓����鋗��
	const float ATTACK_DISTANCE = 3.0f;
	// �U���̓����锻��͈�
	const float ATTACK_DOT = 0.5f;
	// �U�������������ۂ̃J�����U���̋��x
	const float CAMERA_INTENSITY = 0.2f;
	// �U�������������ۂ̃J�����U���̎���
	const float CAMERA_DURATION = 0.4f;
	// ���x�̕␳
	const float APPLY_VELOCITY = 0.08f;

private:
	// �~���[�^���g
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantJumpingAnimation> m_animation;
	// �v���C���[�̃|�C���^
	Player* m_player;
};
