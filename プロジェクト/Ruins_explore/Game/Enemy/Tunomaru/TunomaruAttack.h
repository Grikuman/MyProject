/*
	�t�@�C�����FTunomaruAttack.h
	�@�@�@�T�v�F�̂܂�̍U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Effect/DebrisEffect.h"

// �O���錾
class Tunomaru;

class TunomaruAttack : public IEnemyState
{
public:
	// �R���X�g���N�^
	TunomaruAttack(Tunomaru* tunomaru);
	// �f�X�g���N�^
	~TunomaruAttack() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;
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
	// �j�ЃG�t�F�N�g
	std::unique_ptr<DebrisEffect> m_debrisEffect;
	// �ҋ@����
	float m_stayTime;
	// �ːi����
	float m_rushTime;
};
