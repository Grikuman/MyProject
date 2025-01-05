/*
	�t�@�C�����FRockBossDown.h
	�@�@�@�T�v�F��{�X�̃_�E����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class Tunomaru;

class RockBossDown : public IEnemyState
{
public:
	// �R���X�g���N�^
	RockBossDown(RockBoss* RockBoss);
	// �f�X�g���N�^
	~RockBossDown();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();
private:
	// ����
	const float MAX_DOWNTIME = 180.f;

private:
	// ��{�X
	RockBoss* m_rockBoss;
	// ���f��
	DirectX::Model* m_model;

	// �_�E������
	float m_downTime;
};
