/*
	@file	Scene.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once

// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

// ��ʓI�ȃV�[���N���X
class Scene
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// �f�o�b�O�J����
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;
	
	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	// ��]
	float m_rotation;

	// �t���[���J�E���^
	unsigned int m_frameCounter;

	// �T�C�R���̔z��
	DirectX::SimpleMath::Vector3 m_positions[8];


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
