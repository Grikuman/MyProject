/*
	�t�@�C��: RockBossAttck.h
	�N���X  : ��{�X�A�^�b�N�N���X
*/
#pragma once
#include "Game/Enemy/IEnemyState.h"

// �O���錾
class CommonResources;
class RockBoss;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossAttack : public IEnemyState
{
public:
	// �R���X�g���N�^
	RockBossAttack(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model);
	// �f�X�g���N�^
	~RockBossAttack();
	// ����������
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update();
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �㏈������
	void Finalize();

private:
	// ��{�X
	RockBoss* m_rockBoss;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;
};
