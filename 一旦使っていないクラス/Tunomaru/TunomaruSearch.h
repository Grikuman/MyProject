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
	~TunomaruSearch() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// �v���C���[��ǂ�������
	void ChasePlayer();
	// �T������U����
	void SearchToAttack();

private:
	const float SEARCH_DISTANCE = 5.0f;

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// ���f��
	DirectX::Model* m_model;
};
