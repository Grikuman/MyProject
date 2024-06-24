/*
	@file	Player.h
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

class Player
{
private:
	CommonResources* m_commonResources;                    // ���ʃ��\�[�X
	
	std::unique_ptr<NRLib::TPS_Camera> m_camera;           // �J����

	std::unique_ptr<mylib::GridFloor> m_gridFloor;         // �i�q��

	std::unique_ptr<Collision> m_collision;                // �����蔻��
private:
	std::unique_ptr<DirectX::Model> m_model;               // �v���C���[�̃��f��

	DirectX::SimpleMath::Vector3 m_position;               // �v���C���[�̍��W

	DirectX::SimpleMath::Vector3 m_speed;                  // �v���C���[�̑��x(X,Y,Z)

	DirectX::SimpleMath::Vector3 m_velocity;               // �v���C���[�̃W�����v���x

	DirectX::SimpleMath::Quaternion m_rotate;              // �v���C���[�̉�](�N�H�[�^�j�I���F���f����])

	bool m_isJumping;                                      // �v���C���[���W�����v���Ă��邩

	float m_cameraRotate;                                  // �J�����̉�]�l

	DirectX::SimpleMath::Matrix m_world;                   // ���[���h�s��

public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
