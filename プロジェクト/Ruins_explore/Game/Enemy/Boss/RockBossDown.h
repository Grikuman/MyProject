/*
	�t�@�C��: RockBossDown.h
	�N���X  : ��{�X�_�E���N���X
*/
#pragma once
#include "Game/Enemy/IEnemyState.h"

// �O���錾
class CommonResources;
class Tunomaru;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossDown : public IEnemyState
{
public:
	// �R���X�g���N�^
	RockBossDown(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model);
	// �f�X�g���N�^
	~RockBossDown();
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
	RockBoss* m_rockBoss;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;

	// �_�E������
	float m_downTime;
	// ����
	const float MAX_DOWNTIME = 90.f;
};
