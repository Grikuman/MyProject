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
	m_angle{},
	m_blendState{}
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


	// ���Z�����P�F��ʓI�ȏ�����
	//D3D11_BLEND_DESC blendDesc{};
	//blendDesc.AlphaToCoverageEnable					= FALSE;
	//blendDesc.IndependentBlendEnable				= FALSE;
	//blendDesc.RenderTarget[0].BlendEnable			= TRUE;
	//blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_COLOR;
	//blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_DEST_COLOR;
	//blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
	//blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	//blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
	//blendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	//blendDesc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	// ���Z�����Q�F�V����������
	CD3D11_DEFAULT defaultSettings{};
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;

	// �u�����h�X�e�[�g���쐬����
	DX::ThrowIfFailed(device->CreateBlendState(&blendDesc, m_blendState.ReleaseAndGetAddressOf()));
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update()
{
	// �f�o�b�O�J�������X�V����
	m_debugCamera->Update(m_commonResources->GetInputManager());

	//// �O�p�`����]����
	//m_angle++;
	//if (m_angle > 360.0f)
	//{
	//	m_angle = 0.0f;
	//}
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


	// �s�������f����`�悷��
	m_model->Draw(context, *states, world, view, m_projection);


	// �������f����`�悷��===================================
	// �e��z��
	std::vector<Vector3> poss;	// �T�C�R���̍��W�z��
	std::vector<Matrix> worlds;	// �T�C�R����world�s��̔z��

	// �T�C�R���̍��W��z��ɒǉ�����
	poss.emplace_back(Vector3{ -2.0f, 0.0f, -0.5f });
	poss.emplace_back(Vector3{  4.0f, 0.0f, -1.0f });
	poss.emplace_back(Vector3{  2.0f, 0.0f, -0.5f });


	// �f�o�b�O�J�����̍��W���擾����
	const Vector3 cameraPos = m_debugCamera->GetEyePosition();

	// �J�������牓�����ɃT�C�R���̍��W����ёւ���
	std::sort(poss.begin(), poss.end(), [&](const Vector3& v1, const Vector3& v2)
		{
			float d1 = Vector3::DistanceSquared(v1, cameraPos);
			float d2 = Vector3::DistanceSquared(v2, cameraPos);
			return d1 > d2;
		}
	);

	// ���ёւ���̔z����g���āAworld�s����v�Z����
	for (const auto& pos : poss)
	{
		worlds.emplace_back(Matrix::CreateTranslation(pos));
	}

	// �������̃T�C�R���́A�J�������牓�����ɕ`�悷��
	for (const auto& world2 : worlds)
	{
		m_model->Draw(
			context,
			*states,
			world2,
			view,
			m_projection,
			false,
			[&]()	// �����_��
			{
				// �u�����h�X�e�[�g��ݒ肷��
				context->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);

				// �[�x�o�b�t�@�́uDepthDefault�v���w�肷��
				//context->OMSetDepthStencilState(states->DepthNone(), 0);	// �~
				context->OMSetDepthStencilState(states->DepthDefault(), 0);	// �Z
			}
		);
	}


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
