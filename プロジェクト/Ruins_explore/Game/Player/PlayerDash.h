/*
	@file	PlayerDash.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once
#include "IState.h"
#include <GeometricPrimitive.h>

// �O���錾
class CommonResources;
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class PlayerDash : public IState
{
public:
	// �R���X�g���N�^
	PlayerDash(Player* player, const std::unique_ptr<DirectX::Model>& model);
	// �f�X�g���N�^
	~PlayerDash();
	// ����������
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	//�v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;
	
	// �_�b�V�����s������
	static const int DASHTIME = 30;
	// �_�b�V������
	float m_dashTime;
};
