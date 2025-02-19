/*
	�t�@�C�����FTunomaruAttack.h
	�@�@�@�T�v�F�̂܂�̍U����Ԃ��Ǘ�����N���X
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
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();
private:
	void Rush();

private:
	// �ҋ@����
	const float MAX_STAYTIME = 30.0f;
	// �ːi����
	const float MAX_RUSHTIME = 120.0f;

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// ���f��
	DirectX::Model* m_model;
	// �ҋ@����
	float m_stayTime;
	// �ːi����
	float m_rushTime;
};
