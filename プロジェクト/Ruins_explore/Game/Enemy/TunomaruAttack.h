/*
	@file	PlayerDash.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once
#include "IEnemyState.h"
#include <GeometricPrimitive.h>

// �O���錾
class CommonResources;
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
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update();
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �㏈������
	void Finalize();

private:
	// �̂܂�
	Tunomaru* m_tunomaru;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;

	// �ːi����
	float m_rushTime;
	float MAX_RUSHTIME = 120.f;
};
