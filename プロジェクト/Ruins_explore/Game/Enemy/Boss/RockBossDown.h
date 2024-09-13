/*
	�t�@�C��: RockBossDown.h
	�N���X  : ��{�X�_�E���N���X
*/
#pragma once
#include "Game/Enemy/IEnemyState.h"

// �O���錾
class Tunomaru;

class RockBossDown : public IEnemyState
{
public:
	// �R���X�g���N�^
	RockBossDown(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model);
	// �f�X�g���N�^
	~RockBossDown();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �̂܂�
	RockBoss* m_rockBoss;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;

	// �_�E������
	float m_downTime;
	// ����
	const float MAX_DOWNTIME = 90.f;
};
