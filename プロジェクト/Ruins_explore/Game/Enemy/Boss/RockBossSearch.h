/*
	�t�@�C��: RockBossSearch.h
	�N���X  : ��{�X�T�[�`�N���X
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

class RockBossSearch : public IEnemyState
{
public:
	// �R���X�g���N�^
	RockBossSearch(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model);
	// �f�X�g���N�^
	~RockBossSearch();
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
