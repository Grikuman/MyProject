/*
	@file	Player.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once
#include "IState.h"
#include "PlayerIdling.h"
#include "PlayerAttack.h"

// �O���錾
class CommonResources;
class GeometricPrimitive;
class Collision;



namespace NRLib
{
	class FixedCamera;
	class TPS_Camera;
};

class Player
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �v���C���[�̃A�C�h�����O���
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// �v���C���[�̃A�^�b�N���
	std::unique_ptr<PlayerAttack> m_playerAttack;
	// ���݂̃X�e�[�g
	IState* m_currentState;
public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();

	NRLib::TPS_Camera* GetCamera();
	DirectX::BoundingSphere GetBoundingSphere();
	// �U�����Ă��邩�擾����
	bool GetIsAttack();
	// �X�e�[�g��ύX����
	void ChangeState(IState* newState);
	// �v���C���[�A�C�h�����O���擾����
	PlayerIdling* GetPlayerIdling() const { return m_playerIdling.get(); }
	// �v���C���[�X�g���C�N�t�H���[�f�B���O���擾����
	PlayerAttack* GetPlayerAttack() const { return m_playerAttack.get(); }
};
