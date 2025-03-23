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
//#include "Libraries/MyLib/FPS_Camera.h"
#include "Libraries/MyLib/TPS_Camera.h"
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
	m_playerAngle{},
	m_player{}
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

	// TPS�J�������쐬����
	m_camera = std::make_unique<mylib::TPS_Camera>();

	// �v���C���[�Fteapot
	m_player = GeometricPrimitive::CreateTeapot(context);
	m_playerAngle = 0.0f;
	m_position = Vector3(0.0f, 0.5f, 3.0f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update()
{
	//// �T�C�R������]����
	//m_angle++;
	//if (m_angle > 360.0f)
	//{
	//	m_angle = 0.0f;
	//}

	// �v���C���[�̑���====================================
	// �L�[�{�[�h���擾����
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// �~�܂�
	Vector3 velocity = Vector3::Zero;

	// �O��ړ�
	if (kb.Up)
	{
		velocity = Vector3::Forward;
	}
	else if (kb.Down)
	{
		velocity = Vector3::Backward;
	}

	// ���E��]
	if (kb.Left)
	{
		m_playerAngle++;
	}
	else if (kb.Right)
	{
		m_playerAngle--;
	}

	// �ړ��ʂ𐳋K������
	velocity.Normalize();

	// �ړ��ʂ�␳����
	velocity *= 0.05f;

	// ��]�s����쐬����
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));

	// ��]���������Ď��ۂɈړ�����
	m_position += Vector3::Transform(velocity, matrix);

	// FPS�J�����ʒu���X�V����
	m_camera->Update(m_position, matrix);
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

	// �T�C�R����`�悷��
	m_model->Draw(context, *states, world, view, projection);

	// �v���C���[��`�悷��
	world  = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));
	world *= Matrix::CreateTranslation(m_position);
	m_player->Draw(world, view, projection);

	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("TPS Camera");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
