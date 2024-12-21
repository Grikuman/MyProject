/*
	�t�@�C�����FTunomaruSearch.h
	�@�@�@�T�v�F�̂܂�̍��G��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// �O���錾
class Tunomaru;

class TunomaruSearch : public IEnemyState
{
public:
	// �R���X�g���N�^
	TunomaruSearch(Tunomaru* tunomaru);
	// �f�X�g���N�^
	~TunomaruSearch();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �㏈������
	void Finalize();

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// ���f��
	DirectX::Model* m_model;
};
