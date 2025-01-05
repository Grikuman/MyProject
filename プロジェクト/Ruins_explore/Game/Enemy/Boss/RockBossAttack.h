/*
	�t�@�C�����FRockBossAttack.h
	�@�@�@�T�v�F��{�X�̍U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class RockBoss;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossAttack : public IEnemyState
{
public:
	// �U���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	// �U�����󂯂Ȃ��o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetNoDamageBoundingSphere() const;

public:
	// �R���X�g���N�^
	RockBossAttack(RockBoss* RockBoss);
	// �f�X�g���N�^
	~RockBossAttack();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();
private:
	// �U���J�n�܂ł̎���
	const float ATACKSTART_TIME = 60.f;

	// ��]�U��
	void SpinningAttack();

private:
	// ��{�X
	RockBoss* m_rockBoss;
	// ���f��
	DirectX::Model* m_model;

	// �U���܂ł̗P�\����
	float m_atackStartTime;
	// ��]�J�E���g
	float m_rotateCnt;
};
