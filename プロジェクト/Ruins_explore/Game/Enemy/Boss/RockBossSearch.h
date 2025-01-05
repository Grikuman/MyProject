/*
	�t�@�C�����FRockBossSearch.h
	�@�@�@�T�v�F��{�X�̒T����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class CommonResources;
class RockBoss;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossSearch : public IEnemyState
{
public:
	// �R���X�g���N�^
	RockBossSearch(RockBoss* RockBoss);
	// �f�X�g���N�^
	~RockBossSearch();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();

private:
	void SearchToAttack();

private:
	// ��{�X
	RockBoss* m_rockBoss;
	// ���f��
	DirectX::Model* m_model;
};
