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
	// �U���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	
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
	// �㏈������
	void Finalize() override;

private:
	// �a����U���̏���
	void Slashing();
	// ������Ԃւ̈ڍs����
	void TransitionToWalking();

private:
	// �~���[�^���g
	Mutant* m_mutant;
	// �A�j���[�V����
	std::unique_ptr<MutantSlashingAnimation> m_animation;
};
