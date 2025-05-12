/*
	�t�@�C�����FMutantWalking.h
	�@�@�@�T�v�F�~���[�^���g�̕�����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantWalkingAnimation.h"

// �O���錾
class Mutant;
class Player;

class MutantWalking : public IEnemyState
{
public:
	// �R���X�g���N�^
	MutantWalking();
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
	// ���x�̕␳
	const float APPLY_VELOCITY = 0.08f;
	// �ːi��ԂɈڍs���锻�苗��
	const float RUSHING_DISTANCE = 10.0f;
	// �a�����ԂɈڍs���锻�苗��
	const float SLASHING_DISTANCE = 5.0f;

private:
	// �~���[�^���g�̃|�C���^
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantWalkingAnimation> m_animation;
	// �v���C���[�̃|�C���^
	Player* m_player;
};
