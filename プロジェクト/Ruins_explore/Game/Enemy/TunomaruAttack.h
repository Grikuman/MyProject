/*
	�t�@�C��: TunomaruAttack.h
	�N���X  : �̂܂�A�^�b�N�N���X
*/
#pragma once
#include "IEnemyState.h"

// �O���錾
class Tunomaru;

namespace NRLib
{
	class TPS_Camera;
};

class TunomaruAttack : public IEnemyState
{
public:
	// �R���X�g���N�^
	TunomaruAttack(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model);
	// �f�X�g���N�^
	~TunomaruAttack();
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
	Tunomaru* m_tunomaru;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;

	// �ːi����
	float m_rushTime;
	const float MAX_RUSHTIME = 120.f;
};
