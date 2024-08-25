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
	// �X�e�[�W�̃��f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// �X�e�[�W�̍��W
	DirectX::SimpleMath::Vector3 m_boxPos;
	// �J�����̃|�C���^
	NRLib::TPS_Camera* m_camera;
	// �o�E���f�B���O�{�b�N�X�̊i�[�p
	std::vector<DirectX::BoundingBox> m_vBoundingBox;

public:
	Field();
	~Field();

	void Initialize(CommonResources* resources,NRLib::TPS_Camera* camera);
	void Update();
	void Render();
	void Finalize();
	std::vector<DirectX::BoundingBox> GetFieldCollision();

private:
	std::unique_ptr<DirectX::Model> m_pyramid;

};
