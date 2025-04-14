/*
	�t�@�C�����FMutantAttackingRushing.h
	�@�@�@�T�v�F�~���[�^���g�̓ːi�U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class Mutant;;

namespace NRLib
{
	class TPS_Camera;
};

class MutantAttackingRushing : public IEnemyState
{
public:
	// �U���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetAttackBoundingSphere() const;

public:
	// �R���X�g���N�^
	MutantAttackingRushing(Mutant* mutant);
	// �f�X�g���N�^
	~MutantAttackingRushing() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// �~���[�^���g
	Mutant* m_mutant;
};
