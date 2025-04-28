/*
	�t�@�C�����FMutantRushing.h
	�@�@�@�T�v�F�~���[�^���g�̓ːi��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantRushingAnimation.h"

// �O���錾
class Mutant;;

class MutantRushing : public IEnemyState
{
public:
	// �R���X�g���N�^
	MutantRushing(Mutant* mutant);
	// �f�X�g���N�^
	~MutantRushing() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;


private:
	// �ːi�̏���
	void Rushing();
	// ������Ԃւ̈ڍs����
	void TransitionToWalking();

private:
	// ���x�̕␳
	const float APPLY_VELOCITY = 0.15f;
	// ������ԂɈڍs���锻�苗��
	const float WALKING_DISTANCE = 10.0f;

private:
	// �~���[�^���g
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantRushingAnimation> m_animation;
};
