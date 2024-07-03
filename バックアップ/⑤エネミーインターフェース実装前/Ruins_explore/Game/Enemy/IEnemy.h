/*
	@file	SmallEnemy.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;
class GeometricPrimitive;

namespace NRLib
{
	class TPS_Camera;
}

// ��ʓI�ȃV�[���N���X
class SmallEnemy
{
public:
	enum STATE
	{
		ALIVE,
		DEAD,
	};
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	NRLib::TPS_Camera* m_camera; // �J�����I�u�W�F�N�g�ւ̃|�C���^

	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;

	DirectX::SimpleMath::Vector3 m_position; // ���W

	DirectX::BoundingSphere m_boundingSphere;

	SmallEnemy::STATE m_state;

	bool m_isHit;

	float m_hp;
public:
	SmallEnemy();
	~SmallEnemy();

	void Initialize(CommonResources* resources, NRLib::TPS_Camera* camera, DirectX::SimpleMath::Vector3 position);
	void Update();
	void Render();
	void Finalize();
public:
	// ��Ԃ�ݒ肷��
	void SetState(SmallEnemy::STATE state);
	// ��Ԃ��擾����
	SmallEnemy::STATE GetState() { return m_state; };
	// �_���[�W���󂯂�(�������_���[�W)
	void Hit(float damage) 
	{ 
		m_hp -= damage; 
		m_isHit = true;
	};
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere();
};
