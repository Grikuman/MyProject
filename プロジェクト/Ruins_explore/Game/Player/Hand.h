/*
	@file	Hand.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class GeometricPrimitive;
class Collision;

namespace NRLib
{
	class FixedCamera;
	class TPS_Camera;
};

namespace mylib
{
	class GridFloor;
	class FollowCamera;
};

class Hand
{
public:
	enum STATE
	{
		NONE,
		ATTACKING,
	};
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// �����蔻��
	std::unique_ptr<Collision> m_collision;
	// �v���C���[�̃��f��
	std::unique_ptr<DirectX::Model> m_model;
	// �v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_position;
	// �v���C���[�̑��x(X,Y,Z)
	DirectX::SimpleMath::Vector3 m_speed;
	// �v���C���[�̃W�����v���x
	DirectX::SimpleMath::Vector3 m_jumpSpeed;
	// �W�����v�g���K�[(true��jump������)
	bool m_jumpTrigger;
	// �v���C���[�̉�](�N�H�[�^�j�I���F���f����])
	DirectX::SimpleMath::Quaternion m_rotate;
	// �v���C���[���W�����v���Ă��邩
	bool m_isJumping;
	// �J�����̉�]�l
	float m_cameraRotate;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// ���݂̏��
	Hand::STATE m_state;
public:
	Hand();
	~Hand();

	void Initialize(CommonResources* resources);
	void Update(
		float elapsedTime,
		DirectX::SimpleMath::Vector3 speed,
		DirectX::SimpleMath::Quaternion rotate
	);
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj);
	void Finalize();
public:
	// �W�����v�g���K�[
	void OnJumpTrigger();
	// �W�����v����
	void Jump();
	// �n���h�̏�Ԃ��擾����
	Hand::STATE GetState() { return m_state; };
};
