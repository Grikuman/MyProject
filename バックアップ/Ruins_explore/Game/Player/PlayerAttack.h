/*
	@file	PlayerAttack.h
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

class PlayerAttack : public IState
{
private:
	//�v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �v���C���[�̃��f��
	std::unique_ptr<DirectX::Model> m_model; 
	// ���W
	DirectX::SimpleMath::Vector3 m_position;      
	// �W�����v���x
	DirectX::SimpleMath::Vector3 m_velocity;  
	// �v���C���[�̊p�x
	float m_playerAngle;
	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;

public:
	PlayerAttack(Player* player);
	~PlayerAttack();

	void Initialize(CommonResources* resources);
	void Update(const float& elapsedTime);
	void Render();
	void Finalize();
	// �J�������擾����
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); }
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere();
};
