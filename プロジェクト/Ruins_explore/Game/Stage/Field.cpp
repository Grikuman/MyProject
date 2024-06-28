/*
	@file	Field.cpp
	@brief	��ʓI�ȃV�[���N���X
*/
#include "pch.h"
#include "Game/Stage/Field.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <GeometricPrimitive.h>
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Field::Field()
	:
	m_commonResources{},
	m_cylinder{},
	m_camera{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Field::~Field()
{
	
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Field::Initialize(CommonResources* resources,NRLib::TPS_Camera* camera)
{
	assert(resources);
	m_commonResources = resources;
	m_camera = camera;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �e�t�B�[���h�I�u�W�F�N�g�̈ʒu��ݒ�
	m_boxPos[0] = Vector3(0.f, -1.f, -20.f);
	m_boxPos[1] = Vector3(0.f, -1.f, -60.f);
	m_cylinderPos[0] = Vector3(0.f, -1.f, 0.f);
	m_cylinderPos[1] = Vector3(0.f, -1.f, -40.f);
	m_cylinderPos[2] = Vector3(0.f, -1.f, -80.f);

	// ���f���𐶐�
	m_box[0] = DirectX::GeometricPrimitive::CreateBox(context, Vector3(4.f, 2.f, 12.f));
	m_box[1] = DirectX::GeometricPrimitive::CreateBox(context, Vector3(4.f, 2.f, 12.f));
	m_cylinder[0] = DirectX::GeometricPrimitive::CreateCylinder(context, 2.f, 30.f);
	m_cylinder[1] = DirectX::GeometricPrimitive::CreateCylinder(context, 2.f, 30.f);
	m_cylinder[2] = DirectX::GeometricPrimitive::CreateCylinder(context, 2.f, 30.f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Field::Update()
{
	
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Field::Render()
{
	// world�s��͏㏑�����Ďg����
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	DirectX::SimpleMath::Matrix view = m_camera->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = m_camera->GetProjectionMatrix();

	// �I�u�W�F�N�g�̕`��
	world = Matrix::CreateTranslation(m_boxPos[0]);
	m_box[0]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_boxPos[1]);
	m_box[0]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_cylinderPos[0]);
	m_cylinder[0]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_cylinderPos[1]);
	m_cylinder[1]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_cylinderPos[2]);
	m_cylinder[2]->Draw(world, view, proj, Colors::SandyBrown);
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Field::Finalize()
{
	// do nothing.
}
