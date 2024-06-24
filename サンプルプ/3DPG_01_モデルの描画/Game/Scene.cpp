/*
	@file	Scene.cpp
	@brief	��ʓI�ȃV�[���N���X
*/
#include "pch.h"
#include "Scene.h"
#include "CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Scene::Scene()
	:
	m_commonResources{},
	m_debugCamera{},
	m_gridFloor{},
	m_projection{},
	m_model{},
	m_angle{}
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

	// �f�o�b�O�J�������쐬����
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	m_debugCamera = std::make_unique<mylib::DebugCamera>();
	m_debugCamera->Initialize(rect.right, rect.bottom);

	// �ˉe�s����쐬����
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 100.0f
	);


	// ��]�p������������i�x�j
	m_angle = 0.0f;


	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/dice.cmo", *fx);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update()
{
	// �f�o�b�O�J�������X�V����
	m_debugCamera->Update(m_commonResources->GetInputManager());

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

	// �r���[�s����擾����
	Matrix view = m_debugCamera->GetViewMatrix();

	// �i�q����`�悷��
	m_gridFloor->Render(context, view, m_projection);

	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateRotationY(XMConvertToRadians(m_angle));


	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, m_projection);


	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Draw 3D Model");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
