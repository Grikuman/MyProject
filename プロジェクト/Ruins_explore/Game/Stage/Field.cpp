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
	m_camera{},
	m_pyramid{}
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
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// �I�u�W�F�N�g���쐬
	m_box = DirectX::GeometricPrimitive::CreateBox(context, Vector3(50.f, 2.f, 50.f));

	// �e�t�B�[���h�I�u�W�F�N�g�̈ʒu��ݒ�
	m_boxPos = Vector3(0.f, -1.f, 0.f);

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// ���f����ǂݍ���
	m_pyramid = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Block.cmo", *fx);
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
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// world�s��͏㏑�����Ďg����
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	DirectX::SimpleMath::Matrix view = m_camera->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = m_camera->GetProjectionMatrix();

	// �I�u�W�F�N�g�̕`��
	world *= Matrix::CreateTranslation(m_boxPos);
	m_box->Draw(world, view, proj, Colors::DarkGray);

	world = Matrix::CreateScale(0.1f);
	world *= Matrix::CreateTranslation(Vector3(0.f, 0.f, 0.f));
	
	//m_pyramid->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Field::Finalize()
{
	// do nothing.
}
