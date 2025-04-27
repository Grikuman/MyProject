/*
	�t�@�C�����FMutantWalking.h
	�@�@�@�T�v�F�~���[�^���g�̕�����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantWalkingAnimation.h"

// �O���錾
class Mutant;

class MutantWalking : public IEnemyState
{
public:
	// �R���X�g���N�^
	MutantWalking(Mutant* mutant);
	// �f�X�g���N�^
	~MutantWalking() override; 
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// �����̏���
	void Walking();
	// �T������U����
	void TransitionToRushing();
	// �a����U����Ԃւ̈ڍs����
	void TransitionToSlashing();

private:
	// �~���[�^���g
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantWalkingAnimation> m_animation;
};
