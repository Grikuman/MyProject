/*
	�t�@�C��: TunomaruAttack.h
	�N���X  : �̂܂�A�^�b�N�N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class Tunomaru;

class TunomaruAttack : public IEnemyState
{
public:
	// �R���X�g���N�^
	TunomaruAttack(Tunomaru* tunomaru);
	// �f�X�g���N�^
	~TunomaruAttack();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();
private:
	// �ːi����
	const float MAX_RUSHTIME = 120.f;

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// ���f��
	DirectX::Model* m_model;

	// �ːi����
	float m_rushTime;
};
