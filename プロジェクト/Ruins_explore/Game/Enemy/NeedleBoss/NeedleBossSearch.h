/*
	�t�@�C�����FNeedleBossSearch.h
	�@�@�@�T�v�F��{�X�̒T����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class CommonResources;
class NeedleBoss;

namespace NRLib
{
	class TPS_Camera;
};

class NeedleBossSearch : public IEnemyState
{
public:
	// �R���X�g���N�^
	NeedleBossSearch(NeedleBoss* needleBoss);
	// �f�X�g���N�^
	~NeedleBossSearch();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();

private:
	// �T������U����
	void SearchToAttack();

private:
	// ��{�X
	NeedleBoss* m_needleBoss;
	// ���f��
	DirectX::Model* m_model;
};
