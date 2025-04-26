/*
	�t�@�C�����FMutantRushing.h
	�@�@�@�T�v�F�~���[�^���g�̓ːi��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantRushingAnimation.h"

// �O���錾
class Mutant;;

namespace NRLib
{
	class TPS_Camera;
};

class MutantRushing : public IEnemyState
{
public:
	// �U���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetAttackBoundingSphere() const;

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
	// �~���[�^���g
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantRushingAnimation> m_animation;
};
