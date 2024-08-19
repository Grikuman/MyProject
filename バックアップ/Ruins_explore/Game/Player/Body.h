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
public:
	//���
	enum STATE
	{
		NONE,       // �������Ă��Ȃ��Ƃ�
		JUMPING,    // �W�����v��
		ATTACKING,     // �U����
	};
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �����蔻��
	std::unique_ptr<Collision> m_collision; 
	// �v���C���[�̃��f��
	std::unique_ptr<DirectX::Model> m_model; 
	// ���W
	DirectX::SimpleMath::Vector3 m_position;  
	// ���x(X,Y,Z)
	DirectX::SimpleMath::Vector3 m_speed;     
	// �W�����v���x
	DirectX::SimpleMath::Vector3 m_velocity;  
	// ��](�N�H�[�^�j�I���F���f����])
	DirectX::SimpleMath::Quaternion m_rotate; 
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;      
	// yaw�֓n���l
	float m_setYaw;                           
	// ���݂̏��
	Body::STATE m_state;
	// �U�����Ă��邩
	bool m_isAttack;
	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// �J�����̉�]�l
	float m_cameraRotate;                       

	// �v���C���[�̕ʃp�[�c
	std::unique_ptr<Hand> m_hand;   // ��p�[�c
	std::unique_ptr<Foot> m_foot;   // ���p�[�c

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
	// �J�������擾����
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); }
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere();
	// �U�����Ă��邩�擾����
	bool GetIsAttack() {return m_isAttack;}
};
