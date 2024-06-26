/*
	@file	Body.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class GeometricPrimitive;
class Collision;

class Hand;
class Foot;

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

class Body
{
	enum STATE
	{
		NONE,       // �������Ă��Ȃ��Ƃ�
		JUMPING,    // �W�����v��
	};
private:
	CommonResources* m_commonResources;                    // ���ʃ��\�[�X

	std::unique_ptr<mylib::GridFloor> m_gridFloor;         // �i�q��

	std::unique_ptr<Collision> m_collision;                // �����蔻��N���X

	// �v���C���[�֘A
	std::unique_ptr<DirectX::Model> m_model;               // �v���C���[�̃��f��
	DirectX::SimpleMath::Vector3 m_position;               // ���W
	DirectX::SimpleMath::Vector3 m_speed;                  // ���x(X,Y,Z)
	DirectX::SimpleMath::Vector3 m_velocity;               // �W�����v���x
	DirectX::SimpleMath::Quaternion m_rotate;              // ��](�N�H�[�^�j�I���F���f����])
	DirectX::SimpleMath::Matrix m_world;                   // ���[���h�s��
	float m_setYaw;                                        // yaw�֓n���l
	Body::STATE m_state;                                   // �X�e�[�g

	// �J�����֘A
	std::unique_ptr<NRLib::TPS_Camera> m_camera;           // �J����
	float m_cameraRotate;                                  // �J�����̉�]�l

	// �v���C���[�̕ʃp�[�c
	std::unique_ptr<Hand> m_hand;                          // ��p�[�c
	std::unique_ptr<Foot> m_foot;                          // ���p�[�c

public:
	Body();
	~Body();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
private:
	void InputProcessing(); // �L�[���́F�R���g���[���[���͂��󂯕t���ē�������߂�
	void Calculation();     // ���͌�Ɍv�Z�������Ȃ�
public:
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); } // �J�������擾

	// �Փ˔���p��AABB��Ԃ�
	DirectX::BoundingSphere GetBoundingSphere();
};
