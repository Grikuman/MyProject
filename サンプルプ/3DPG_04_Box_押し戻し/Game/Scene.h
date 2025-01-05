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

	//// �x�[�V�b�N�G�t�F�N�g
	//std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	//// �v���~�e�B�u�o�b�`
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	//// ���̓��C�A�E�g
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �f�o�b�O�J����
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;
	
	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;


	// ���ȉ��A�ǋL����ϐ��Ȃǁ�

	// �W�I���g���b�N�v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// ��]�p�i�x�j
	float m_angle;
	// ���W
	DirectX::SimpleMath::Vector3 m_positionA;
	DirectX::SimpleMath::Vector3 m_positionB;
	// ����
	static constexpr float SPEED = 0.05f;
	// �q�b�g�t���O
	bool m_isHit;
	// �o�E���f�B���O�{�b�N�X
	DirectX::BoundingBox m_boundingBoxA;
	DirectX::BoundingBox m_boundingBoxB;

public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();

private:
	// �Փ˔���
	void CheckHit();
};
