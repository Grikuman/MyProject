/*
	@file	Scene.cpp
	@brief	��ʓI�ȃV�[���N���X
*/
#include "pch.h"
#include "Scene.h"
#include "CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
//#include "Libraries/MyLib/FixedCamera.h"
#include "Libraries/MyLib/FPS_Camera.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Scene::Scene()
	:
	m_commonResources{},
	m_gridFloor{},
	m_model{},
	m_angle{},
	m_camera{},
	m_position{},
	m_velocity{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Scene::~Scene()
{
	Finalize();
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Scene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = m_commonResources->GetCommonStates();


	// �O���b�h�����쐬����
	m_gridFloor = std::make_unique<mylib::GridFloor>(device, context, states);

	// ��]�p������������i�x�j
	m_angle = 0.0f;

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/dice.cmo", *fx);

	// FPS�J�������쐬����
	m_camera = std::make_unique<mylib::FPS_Camera>();

	m_position = m_camera->GetEyePosition();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update()
{
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// �~�܂�
	m_velocity = Vector3::Zero;

	// �O��ړ�
	if (kb.Up)
	{
		m_velocity = Vector3::Forward;
	}
	else if (kb.Down)
	{
		m_velocity = Vector3::Backward;
	}

	// ���E�ړ�
	if (kb.Left)
	{
		m_velocity = Vector3::Left;
	}
	else if (kb.Right)
	{
		m_velocity = Vector3::Right;
	}

	// �ړ��ʂ𐳋K������
	m_velocity.Normalize();

	// �ړ��ʂ�␳����
	m_velocity *= 0.05f;

	// ���ۂɈړ�����
	m_position += m_velocity;

	// FPS�J�����ʒu���X�V����
	m_camera->Update(m_position);


	// �O�p�`����]����
	m_angle++;
	if (m_angle > 360.0f)
	{
		m_angle = 0.0f;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Scene::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// �J��������r���[�s��Ǝˉe�s����擾����
	Matrix view = m_camera->GetViewMatrix();
	Matrix projection = m_camera->GetProjectionMatrix();

	// �i�q����`�悷��
	m_gridFloor->Render(context, view, projection);

	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateRotationY(XMConvertToRadians(m_angle));


	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, projection);


	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("FPS Camera");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
