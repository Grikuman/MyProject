/*
	@file	Player.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once
#include "IState.h"
#include "PlayerIdling.h"
#include "PlayerAttack.h"
#include "PlayerDash.h"

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
public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();
	// ����������
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update(float elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();
public:
	// �v���C���[�A�C�h�����O���擾����
	PlayerIdling* GetPlayerIdling() { return m_playerIdling.get(); }
	// �v���C���[�A�^�b�N���擾����
	PlayerAttack* GetPlayerAttack() { return m_playerAttack.get(); }
	// �v���C���[�_�b�V�����擾����
	PlayerDash* GetPlayerDash() { return m_playerDash.get(); }

public:
	// �ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// ���x���擾����
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// �p�x���擾����
	float GetAngle() const { return m_playerAngle; }

	// �U�����Ă��邩�擾����
	bool GetIsAttack();
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere();

	// �J�������擾����
	NRLib::TPS_Camera* GetCamera();

public:
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// �p�x��ݒ肷��
	void SetAngle(const float angle) { m_playerAngle = angle; }

	// �X�e�[�g��ύX����
	void ChangeState(IState* newState);
private:
	// ���݂̃X�e�[�g
	IState* m_currentState;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	// �A�C�h�����O���
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// �A�^�b�N���
	std::unique_ptr<PlayerAttack> m_playerAttack;
	// �_�b�V�����
	std::unique_ptr<PlayerDash> m_playerDash;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �p�x
	float m_playerAngle;
};
