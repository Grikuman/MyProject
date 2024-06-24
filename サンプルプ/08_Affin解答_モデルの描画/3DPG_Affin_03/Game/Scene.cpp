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
	m_view{},
	m_projection{},
	m_model{},
	m_rotation{},
	m_frameCounter{},
	m_positions{}
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

	// �r���[�s����쐬����
	Vector3 eye{ 0,5,10 };
	Vector3 target{ Vector3::Zero };
	m_view = Matrix::CreateLookAt(eye, target, Vector3::UnitY);

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// �T�C�R�����f�������[�h����
	m_model = Model::CreateFromCMO(device, L"Resources/Models/dice.cmo", *fx);

	// �p�����[�^������������
	m_rotation = 0.0f;
	m_frameCounter = 0;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �f�o�b�O�J�������X�V����
	m_debugCamera->Update(m_commonResources->GetInputManager());

	// �t���[�������J�E���g����
	m_frameCounter++;
	m_frameCounter %= 360;

	// ��]����
	m_rotation += 0.3f;
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
	//m_gridFloor->Render(context, m_view, m_projection);

	// ���[���h�s��i�g���܂킵�j
	Matrix world = Matrix::Identity;

	// �����̃T�C�R����`�悷��
	world = Matrix::CreateRotationY(XMConvertToRadians(-m_rotation));
	m_model->Draw(context, *states, world, view, m_projection);
	//m_model->Draw(context, *states, world, m_view, m_projection);

	// �W�̃T�C�R����`�悷��
	for (size_t i = 0; i < 4; i++)
	{
		// �z�u����
		m_positions[i] = Vector3{
			0,
			0 + std::sin((XM_PIDIV2 * i) + XMConvertToRadians(static_cast<float>(m_frameCounter))),
			3
		};

		// ��]����
		world  = Matrix::CreateTranslation(m_positions[i]);
		world *= Matrix::CreateRotationY(XMConvertToRadians(90.0f * i + m_rotation));

		// �T�C�R����`�悷��
		m_model->Draw(context, *states, world, view, m_projection);
		//m_model->Draw(context, *states, world, m_view, m_projection);
	}


	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Practice");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
