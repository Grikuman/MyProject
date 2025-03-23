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
	m_teapot{},
	m_box{},
	m_quaternion{},
	m_teapotPosition{},
	m_boxPosition{}
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

	// �W�I���g���b�N�v���~�e�B�u���쐬����
	m_teapot = GeometricPrimitive::CreateTeapot(context);
	m_box = GeometricPrimitive::CreateBox(context, Vector3(1.0f, 1.0f, 0.5f));

	// �e�B�[�|�b�g��Box�̍��W���`����
	m_teapotPosition = Vector3::Backward * 2.0f;
	m_boxPosition = Vector3::Forward * 2.0f;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �f�o�b�O�J�������X�V����
	m_debugCamera->Update(m_commonResources->GetInputManager());

	// �L�[�{�[�h�X�e�[�g���擾����
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// Box�̍��W�𑀍삷��
	if (kb.Left)	m_boxPosition.x -= 0.1f;
	if (kb.Right)	m_boxPosition.x += 0.1f;
	if (kb.Up)		m_boxPosition.y += 0.1f;
	if (kb.Down)	m_boxPosition.y -= 0.1f;

	// �e�B�[�|�b�g�̎����x�N�g�����v�Z����
	Vector3 lookAt = m_boxPosition - m_teapotPosition;

	// ���E�����̃x�N�g���Ə㉺�����̃x�N�g�����v�Z����
	Vector3 tmp = lookAt;
	tmp.y = 0.0f;
	Vector3 lookAtYaw = tmp;
	tmp = lookAt;
	tmp.x = 0.0f;
	Vector3 lookAtPitch = tmp;

	// �p�x�i�ƃ��W�A���j���v�Z����
	float yawAngle = std::acos(lookAtYaw.Dot(Vector3::Forward) / lookAtYaw.Length() * Vector3::Forward.Length());
	float pitchAngle = std::acos(lookAtPitch.Dot(Vector3::Forward) / lookAtPitch.Length() * Vector3::Forward.Length());
	float rollAngle = 0.0f;

	// �O�ς���e�B�[�|�b�g�������ׂ��������v�Z����
	// ������
	Vector3 cross = Vector3::Forward.Cross(lookAtYaw);
	if (cross.y < 0.0f)
	{
		yawAngle *= (-1.0f);
	}
	// �c����
	cross = Vector3::Forward.Cross(lookAtPitch);
	if (cross.x < 0)
	{
		pitchAngle *= (-1.0f);
	}

	// ��]�p���v�Z����
	m_quaternion = Quaternion::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Scene::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �r���[�s����擾����
	Matrix view = m_debugCamera->GetViewMatrix();

	// �i�q����`�悷��
	m_gridFloor->Render(context, view, m_projection);

	// Teapot�̃��[���h�s����X�V����
	Matrix teapotWorld = Matrix::CreateFromQuaternion(m_quaternion);
	teapotWorld *= Matrix::CreateTranslation(m_teapotPosition);

	// Box�̃��[���h�s����X�V����
	Matrix boxWorld = Matrix::CreateTranslation(m_boxPosition);

	// �W�I���g���b�N�v���~�e�B�u��`�悷��
	m_teapot->Draw(teapotWorld, view, m_projection, Colors::Gold);
	m_box->Draw(boxWorld, view, m_projection);

	// �f�o�b�O�h���[�Ŏ���\������
	Vector3 forward    = Vector3::Transform(Vector3(0.0f, 0.0f, 1.5f), m_quaternion);
	Vector3 horizontal = Vector3::Transform(Vector3(1.5f, 0.0f, 0.0f), m_quaternion);
	Vector3 vertical   = Vector3::Transform(Vector3(0.0f, 1.5f, 0.0f), m_quaternion);

	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(m_projection);
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();
	DX::DrawRay(m_primitiveBatch.get(), m_boxPosition, forward,    false, Colors::Cyan);
	DX::DrawRay(m_primitiveBatch.get(), m_boxPosition, horizontal, false, Colors::Red);
	DX::DrawRay(m_primitiveBatch.get(), m_boxPosition, vertical,   false, Colors::GreenYellow);
	m_primitiveBatch->End();

	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Sample Quaternion");
	debugString->AddString("");

	// �N�H�[�^�j�I������I�C���[�p�����o��
	Vector3 euler = m_quaternion.ToEuler();

	// �f�o�b�O����\������
	debugString->AddString("eulerX : %f", XMConvertToDegrees(euler.x));
	debugString->AddString("eulerY : %f", XMConvertToDegrees(euler.y));
	debugString->AddString("eulerZ : %f", XMConvertToDegrees(euler.z));
	debugString->AddString("");
	debugString->AddString("< Key Operation >");
	debugString->AddString("pitch : Up or Down");
	debugString->AddString("yaw : Left or Right");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
