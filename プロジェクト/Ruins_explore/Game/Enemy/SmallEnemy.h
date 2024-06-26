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
public:
	SmallEnemy();
	~SmallEnemy();

	void Initialize(CommonResources* resources, NRLib::TPS_Camera* camera, DirectX::SimpleMath::Vector3 position);
	void Update();
	void Render();
	void Finalize();
public:
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }

	void SetState(SmallEnemy::STATE state);
	DirectX::BoundingSphere GetBoundingSphere();

};
