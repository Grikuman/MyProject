/*
	�t�@�C�����FMutantStunned.h
	�@�@�@�T�v�F��{�X�̃_�E����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Effect/DownEffect.h"

// �O���錾
class NeedleBoss;

class MutantStunned : public IEnemyState
{
public:
	// �R���X�g���N�^
	MutantStunned(NeedleBoss* needleBoss);
	// �f�X�g���N�^
	~MutantStunned() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;
private:
	// �ݒ肷��_�E������
	const float MAX_DOWNTIME = 240.f;

private:
	// ��{�X
	NeedleBoss* m_needleBoss;
	// �G�t�F�N�g
	std::unique_ptr<DownEffect> m_effect;
	// ���f��
	DirectX::Model* m_model;
	// �_�E������
	float m_downTime;
};
