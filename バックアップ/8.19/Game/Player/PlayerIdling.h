/*
	@file	PlayerIdling.h
	@brief	�v���C���[�V�[���N���X
*/
#pragma once
#include "IState.h"
#include <GeometricPrimitive.h>
#include "WorkTool/Collision.h"

// �O���錾
class CommonResources;
class Player;

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

class PlayerIdling : public IState
{
private:
	//�v���C���[
	Player* m_player;
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
	// ��]
	DirectX::SimpleMath::Quaternion m_rotate;
	// �v���C���[�̊p�x
	float m_playerAngle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;      
	// yaw�֓n���l
	float m_setYaw;                           
	// �U�����Ă��邩
	bool m_isAttack;
	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// �J�����̉�]�l
	float m_cameraRotate;

public:
	PlayerIdling(Player* player);
	~PlayerIdling();

	void Initialize(CommonResources* resources);
	void Update(const float& elapsedTime);
	void Render();
	void Finalize();
	// �J�������擾����
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); }
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere();
private:
	// �ʂ̍s���ֈڍs���鏈��
	void ChangeState();
public:
	// �U�����Ă��邩�擾����
	bool GetIsAttack() {return m_isAttack;}
};
