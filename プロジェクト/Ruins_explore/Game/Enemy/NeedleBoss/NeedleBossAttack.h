/*
	�t�@�C�����FNeedleBossAttack.h
	�@�@�@�T�v�F��{�X�̍U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class NeedleBoss;;

namespace NRLib
{
	class TPS_Camera;
};

class NeedleBossAttack : public IEnemyState
{
public:
	// �U���̎��
	enum class AttackType
	{
		Spinning,
		Charging
	};
public:
	// �U���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	// �U�����󂯂Ȃ��o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetNoDamageBoundingSphere() const;

public:
	// �R���X�g���N�^
	NeedleBossAttack(NeedleBoss* needleBoss);
	// �f�X�g���N�^
	~NeedleBossAttack();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();
private:
	// ��]�U��
	void SpinningAttack();
	// �ːi�U��
	void ChargingAttack();

private:
	// �U���J�n�܂ł̎���
	const float ATACKSTART_TIME = 60.0f;

private:
	// ��{�X
	NeedleBoss* m_needleBoss;
    // ���݂̍U���^�C�v
	AttackType m_attackType; 
	// ���f��
	DirectX::Model* m_model;

	// �U���܂ł̗P�\����
	float m_atackStartTime;
	// ��]�J�E���g
	float m_rotateCnt;
};
