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
	m_position{}
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
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Plane.cmo", *fx);


	// ��s�@�̏����p����ݒ肷��c�@
	// fromDir����toDir�֌������]�����A�����ł́A�x����180�x��]
	m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);

	//// ��s�@�̏����p����ݒ肷��c�A
	//// �[���x�̉�]�A��]�̃��Z�b�g
	//m_rotate = Quaternion::Identity;

	/*
		���FInitialize��Update�ŁA��]�̏����l�����킹�邱�Ɓi�@�Ƈ@�A�A�ƇA�j
	*/

	// ��s�@�̍��W������������
	m_position = Vector3::Zero;


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

	// �y�L�[�Ŕ�s�@�̋��������Z�b�g����
	if (kbTracker->pressed.Z)
	{
		// ��]�̃��Z�b�g�c�@
		m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);

		//// ��]�̃��Z�b�g�c�A
		//m_rotate = Quaternion::Identity;

		// ���W�����Z�b�g����
		m_position = Vector3::Zero;
	}

	// �L�[�{�[�h�X�e�[�g���擾����
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// ���[���A�s�b�`�A���[
	float roll  = 0.0f;	// �y����]
	float pitch = 0.0f;	// �w����]
	float yaw   = 0.0f;	// �x����]

	if (kb.A)		roll  = XMConvertToRadians(-1.0f);	// �������̌����ڏd���̉�]�����邽�߁Aroll�̂݁{�|�𔽓]����
	if (kb.D)		roll  = XMConvertToRadians( 1.0f);
	if (kb.W)		pitch = XMConvertToRadians( 1.0f);
	if (kb.S)		pitch = XMConvertToRadians(-1.0f);
	if (kb.Left)	yaw   = XMConvertToRadians( 1.0f);
	if (kb.Right)	yaw   = XMConvertToRadians(-1.0f);

	// �N�H�[�^�j�I�������[���A�s�b�`�A���[�̒l���琶������
	Quaternion q = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);

	// ��]
	m_rotate = q * m_rotate;	// �@
	//m_rotate *= q;	// �A

	 /*
		�����[���A�s�b�`�A���[
		�EDirectX�ł́A���[���F�y����]�A�s�b�`�F�w����]�A���[�F�x����]

		����]
		�EDirectXTK�̉E����W�n�ł́A�v���X�����������v���A�}�C�i�X���������v���ɂȂ�i���P�j
		���P�F�e���̃v���X�������猴�_�������ꍇ�̉�]�����A�E�˂��̖@��

		���N�H�[�^�j�I���̉�]�̐�
		�@�I�u�W�F�N�g�̃��[�J�����W�ŉ�]���������Ƃ�
		�E�um_rotate = q * m_rotate;�v
		�E�@�̕��@���I�u�W�F�N�g�̉�]����ɂ͒��ϓI�Ɏg�p�ł���
		https://qiita.com/yaegaki/items/4d5a6af1d1738e102751

		�A��]���̓��[���h�̒��s���W����ɂȂ�
		�E�um_rotate *= q;�vor�um_rotate = m_rotate * q;�v
		�EXMQuaternionMultiply(q1,q2)�̂Ƃ��Aq1�̉�]��Aq2�̉�]������
		���u*=�v�͓����I�ɁuXMQuaternionMultiply�v�����s�����iq1 *= q2;�j
		���uq1�v�uq2�v�̓N�H�[�^�j�I��

		���uSimpleMath::Quaternion::CreateFromYawPitchRoll(yaw,pitch,roll)�v�ɂ���
		�E�����I�ɁuDirecttX::XMQuaternionRotationRollPitchYaw(pitch,yaw,roll)�v���Ă΂��
	 */

	 // ���W���X�V����
	if (kb.Up)		m_position += Vector3::Transform(Vector3(0.0f, 0.0f,  0.1f), m_rotate);
	if (kb.Down)	m_position += Vector3::Transform(Vector3(0.0f, 0.0f, -0.1f), m_rotate);
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
	Vector3 forward    = Vector3::Transform(Vector3(0.0f, 0.0f, 1.5f), m_rotate);
	Vector3 horizontal = Vector3::Transform(Vector3(1.5f, 0.0f, 0.0f), m_rotate);
	Vector3 vertical   = Vector3::Transform(Vector3(0.0f, 1.5f, 0.0f), m_rotate);

	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(m_projection);
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();
	DX::DrawRay(m_primitiveBatch.get(), m_position, forward,    false, Colors::Cyan);
	DX::DrawRay(m_primitiveBatch.get(), m_position, horizontal, false, Colors::Red);
	DX::DrawRay(m_primitiveBatch.get(), m_position, vertical,   false, Colors::GreenYellow);
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
	debugString->AddString("< Key Operation >");
	debugString->AddString("roll : A or D");
	debugString->AddString("pitch : W or S");
	debugString->AddString("yaw : Left or Right");
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
