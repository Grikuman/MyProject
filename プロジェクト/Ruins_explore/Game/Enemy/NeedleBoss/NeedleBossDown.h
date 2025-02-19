/*
	�t�@�C�����FNeedleBossDown.h
	�@�@�@�T�v�F��{�X�̃_�E����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class NeedleBoss;

class NeedleBossDown : public IEnemyState
{
public:
	// �R���X�g���N�^
	NeedleBossDown(NeedleBoss* needleBoss);
	// �f�X�g���N�^
	~NeedleBossDown();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();
private:
	// �ݒ肷��_�E������
	const float MAX_DOWNTIME = 180.f;

private:
	// ��{�X
	NeedleBoss* m_needleBoss;
	// ���f��
	DirectX::Model* m_model;
	// �_�E������
	float m_downTime;
};
