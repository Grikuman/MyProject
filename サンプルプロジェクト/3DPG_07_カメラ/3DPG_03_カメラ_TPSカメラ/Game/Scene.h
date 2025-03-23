/*
	@file	Scene.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;

namespace mylib
{
	class GridFloor;
	class TPS_Camera;
}

// ��ʓI�ȃV�[���N���X
class Scene
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;


	// ���ȉ��A�ǋL����ϐ��Ȃǁ�

	// ���f���̕`��Ŏg�p����
	std::unique_ptr<DirectX::Model> m_model;	// ���f��
	float							m_angle;	// ��]�p�i�x�j

	std::unique_ptr<mylib::TPS_Camera> m_camera;	// TPS�J����

	DirectX::SimpleMath::Vector3 m_position;		// �v���C���[���W
	float m_playerAngle;							// �v���C���[�̊p�x�i�x�j
	// �W�I���g���b�N�v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_player;


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
};
