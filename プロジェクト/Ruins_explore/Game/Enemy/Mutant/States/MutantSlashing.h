/*
	�t�@�C�����FMutantSlashing.h
	�@�@�@�T�v�F�~���[�^���g�̎a�����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantSlashingAnimation.h"

// �O���錾
class Mutant;

namespace NRLib
{
	class TPS_Camera;
};

class MutantSlashing : public IEnemyState
{
public:
	// �R���X�g���N�^
	MutantSlashing(Mutant* mutant);
	// �f�X�g���N�^
	~MutantSlashing() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �a����U���̏���
	void Slashing();
	// ������Ԃւ̈ڍs����
	void TransitionToWalking();

private:
	// �U���̓����鋗��
	const float ATTACK_DISTANCE = 5.0f;
	// �U�������������ۂ̃J�����U���̋��x
	const float CAMERA_INTENSITY = 0.2f;
	// �U�������������ۂ̃J�����U���̎���
	const float CAMERA_DURATION = 0.4f;

private:
	// �~���[�^���g
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantSlashingAnimation> m_animation;
};
