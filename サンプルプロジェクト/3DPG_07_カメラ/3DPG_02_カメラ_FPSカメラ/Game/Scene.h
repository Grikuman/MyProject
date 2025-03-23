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
	class FPS_Camera;
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

	std::unique_ptr<mylib::FPS_Camera> m_camera;	// FPS�J����

	DirectX::SimpleMath::Vector3 m_position;		// ��l�̎��_
	DirectX::SimpleMath::Vector3 m_velocity;		// �ړ��x�N�g��


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
};
