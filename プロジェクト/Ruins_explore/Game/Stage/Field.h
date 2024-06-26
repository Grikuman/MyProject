/*
	@file	Field.h
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
class Field
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	std::unique_ptr<DirectX::GeometricPrimitive> m_box[2];
	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder[3];

	DirectX::SimpleMath::Vector3 m_boxPos[2];
	DirectX::SimpleMath::Vector3 m_cylinderPos[3];

	NRLib::TPS_Camera* m_camera; // �J�����I�u�W�F�N�g�ւ̃|�C���^

public:
	Field();
	~Field();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
public:
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }
};
