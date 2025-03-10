/*
	�t�@�C�����FTunomaruKnockback.h
	�@�@�@�T�v�F�̂܂�̐�����я�Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class Tunomaru;

class TunomaruKnockback : public IEnemyState
{
public:
	// �R���X�g���N�^
	TunomaruKnockback(Tunomaru* tunomaru);
	// �f�X�g���N�^
	~TunomaruKnockback() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;
private:
	// �ːi����
	const float MAX_KNOCKBACK_TIME = 120.0f;

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// �ːi����
	float m_knockbackTime;
};
