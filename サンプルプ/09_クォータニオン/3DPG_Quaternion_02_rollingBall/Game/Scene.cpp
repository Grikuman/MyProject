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
#include "Libraries/Microsoft/DebugDraw.h"
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
	m_primitiveBatch{},
	m_inputLayout{},
	m_basicEffect{},
	m_model{},
	m_rotate{},
	m_position{},
	m_forward{},
	m_horizontal{},
	m_speed{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Scene::~Scene()
{
	// do nothing.
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


	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Earth.cmo", *fx);


	// ���f���̉�]�����Z�b�g����
	m_rotate = Quaternion::Identity;

	// ���f���̍��W������������F���ɏ������Ԃɂ���
	m_position = Vector3(0.0f, 0.5f, 0.0f);

	// ���f���̐i�s�����x�N�g��������������F�}�C�i�X�y�������ɂP�̒P�ʃx�N�g��
	m_forward = Vector3::Forward;


	// DebugDraw�Ő�����`�悷�邽�߂̏���
	// �um_basicEffect�v�um_primitiveBatch�v�um_inputLayout�v�̂R�̃I�u�W�F�N�g�𐶐�����
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �f�o�b�O�J�������X�V����
	m_debugCamera->Update(m_commonResources->GetInputManager());

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// �y�L�[�Œn���̋��������Z�b�g����
	if (kbTracker->pressed.Z)
	{
		// �p�����[�^�����Z�b�g����
		m_rotate	= Quaternion::Identity;
		m_position	= Vector3(0.0f, 0.5f, 0.0f);
		m_forward	= Vector3::Forward;
		m_speed		= 0.0f;
	}

	// �L�[�{�[�h�X�e�[�g���擾����
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// �i�s�����x�N�g�����v�Z����i���E�։񓪂���j
	if (kb.Left)
	{
		Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(1.0f));
		m_forward = Vector3::Transform(m_forward, rotY);
	}
	if (kb.Right)
	{
		Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(-1.0f));
		m_forward = Vector3::Transform(m_forward, rotY);
	}

	// �O�i�ƌ��
	if (kb.Up)		{ m_speed += 0.001f; }
	if (kb.Down)	{ m_speed -= 0.001f; }

	// ���C���l������
	m_speed *= 0.98f;

	// ������x�̑����ɂȂ�����A�~�߂�
	if (std::abs(m_speed) < 0.0009f)
	{
		m_speed = 0.0f;
	}

	// ���x�x�N�g��
	Vector3 velocity = m_forward * m_speed;

	// �{�[�����ړ�����
	m_position += velocity;

	// �{�[���̉�]�������߂�
	m_horizontal = Vector3(m_forward.z, 0.0f, -m_forward.x);

	// �{�[������]����
	float angle = velocity.Length() / 0.5f;	// ���a=0.5f
	if (m_speed < 0.0f) { angle *= (-1.0f); }
	m_rotate *= Quaternion::CreateFromAxisAngle(m_horizontal, angle);
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
	Matrix world = Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);

	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, m_projection);

	// �f�o�b�O�h���[�Ŏ���\������
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(m_projection);
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();
	DX::DrawRay(m_primitiveBatch.get(), m_position, m_forward, false, Colors::Cyan);
	DX::DrawRay(m_primitiveBatch.get(), m_position, m_horizontal, false, Colors::Red);
	m_primitiveBatch->End();

	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Sample Quaternion");
	debugString->AddString("");

	// �N�H�[�^�j�I������I�C���[�p�����o��
	Vector3 euler = m_rotate.ToEuler();

	// �f�o�b�O����\������
	debugString->AddString("eulerX : %f", XMConvertToDegrees(euler.x));
	debugString->AddString("eulerY : %f", XMConvertToDegrees(euler.y));
	debugString->AddString("eulerZ : %f", XMConvertToDegrees(euler.z));
	debugString->AddString("");
	debugString->AddString("m_speed : %f", m_speed);
	debugString->AddString("m_forward x=%f,y=%f,z=%f", m_forward.x, m_forward.y, m_forward.z);
	debugString->AddString("m_position x=%f,y=%f,z=%f", m_position.x, m_position.y, m_position.z);
	debugString->AddString("");
	debugString->AddString("< Key Operation >");
	debugString->AddString("direction : Left or Right");
	debugString->AddString("move : Up or Down");
	debugString->AddString("reset : Z");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
