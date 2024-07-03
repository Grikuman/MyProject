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
	// �G�̃��f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_box[2];
	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder[3];
	// �G�̍��W
	DirectX::SimpleMath::Vector3 m_boxPos[2];
	DirectX::SimpleMath::Vector3 m_cylinderPos[3];
	// �J�����̃|�C���^
	NRLib::TPS_Camera* m_camera;

public:
	Field();
	~Field();

	void Initialize(CommonResources* resources,NRLib::TPS_Camera* camera);
	void Update();
	void Render();
	void Finalize();
};
