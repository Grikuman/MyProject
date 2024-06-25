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

	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;

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
