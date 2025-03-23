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
#include <algorithm>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Scene::Scene()
	:
	m_commonResources{},
	//m_basicEffect{},
	//m_primitiveBatch{},
	//m_inputLayout{},
	m_debugCamera{},
	m_gridFloor{},
	m_projection{},
	m_box{},
	m_angle{},
	m_positionA{},
	m_positionB{},
	m_isHit{},
	m_boundingBoxA{},
	m_boundingBoxB{}
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


	// �W�I���g���b�N�v���~�e�B�u�𐶐�����
	m_box = GeometricPrimitive::CreateBox(context, Vector3(1.0f));

	// ��]�p������������i�x�j
	m_angle = 0.0f;

	// ���W������������
	m_positionA = Vector3::Zero;
	m_positionA.x = 2.0f;

	m_positionB = Vector3::Zero;

	// �Փ˃t���O������������
	m_isHit = false;

	// �o�E���f�B���O�{�b�N�X
	m_boundingBoxA.Center = m_positionA;
	m_boundingBoxA.Extents = Vector3(0.5f);
	m_boundingBoxB.Center = m_positionB;
	m_boundingBoxB.Extents = Vector3(0.5f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Scene::Update()
{
	// �f�o�b�O�J�������X�V����
	m_debugCamera->Update(m_commonResources->GetInputManager());


	// �L�[�{�[�h�̏�Ԃ��擾����
	const auto& kbState = m_commonResources->GetInputManager()->GetKeyboardState();
	const auto& tracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// ����
	Vector3 velocity = Vector3::Zero;

	// �O��ړ�
	if (kbState.Up)
	{
		velocity += Vector3::Forward;
	}
	else if (kbState.Down)
	{
		velocity += Vector3::Backward;
	}

	// ���E�ړ�
	if (kbState.Left || kbState.A)
	{
		velocity += Vector3::Left;
	}
	else if (kbState.Right || kbState.D)
	{
		velocity += Vector3::Right;
	}

	// �㉺�ړ�
	if (kbState.W)
	{
		velocity += Vector3::Up;
	}
	else if (kbState.S)
	{
		velocity += Vector3::Down;
	}

	// ���K������
	velocity.Normalize();

	// �ړ��ʂ��v�Z����
	velocity *= SPEED;

	// �ړ��ʂ����W�ɉ��Z����
	m_positionA += velocity;

	// �o�E���f�B���O�{�b�N�X���ړ�����
	m_boundingBoxA.Center = m_positionA;
	m_boundingBoxB.Center = m_positionB;


	// �e����W�̃��Z�b�g
	if (tracker->pressed.Space)
	{
		m_positionA = Vector3::Zero;
		m_positionA.x = 2.0f;
		m_positionB = Vector3::Zero;

		m_boundingBoxA.Center = m_positionA;
		m_boundingBoxB.Center = m_positionB;
	}


	// �Փ˔���
	CheckHit();
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

	// �L���[�u�̃��[���h�s����v�Z����
	Matrix worldA = Matrix::CreateTranslation(m_positionA);
	Matrix worldB = Matrix::CreateTranslation(m_positionB);

	// �W�I���g���b�N�v���~�e�B�u��`�悷��
	// ����Ώ�
	m_box->Draw(worldA, view, m_projection, Colors::Green);
	// �ՓˑΏ�
	if (m_isHit)
	{
		m_box->Draw(worldB, view, m_projection, Colors::Red);
	}
	else
	{
		m_box->Draw(worldB, view, m_projection, Colors::White);
	}

	// �f�o�b�O����\������
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("m_positionA : %f, %f, %f", m_positionA.x, m_positionA.y, m_positionA.z);
	debugString->AddString("m_positionB : %f, %f, %f", m_positionB.x, m_positionB.y, m_positionB.z);
	debugString->AddString("BoundingBoxA : %f, %f, %f", m_boundingBoxA.Center.x, m_boundingBoxA.Center.y, m_boundingBoxA.Center.z);
	debugString->AddString("BoundingBoxB : %f, %f, %f", m_boundingBoxB.Center.x, m_boundingBoxB.Center.y, m_boundingBoxB.Center.z);
	debugString->AddString("IsHit? : %s", m_isHit ? "true" : "false");
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// �Փ˔��肷��
//---------------------------------------------------------
void Scene::CheckHit()
{
	// �o�E���f�B���O�{�b�N�X���m�̏Փ˔�����Ƃ�
	m_isHit = m_boundingBoxA.Intersects(m_boundingBoxB);

	// �q�b�g���Ă��Ȃ���ΏI���
	if (!m_isHit) { return; }
	

	// �Փˎ��A�a���`�������߂�����========================

	// AABB�p��min/max���v�Z����
	Vector3 aMin = m_boundingBoxA.Center - m_boundingBoxA.Extents;
	Vector3 aMax = m_boundingBoxA.Center + m_boundingBoxA.Extents;
	Vector3 bMin = m_boundingBoxB.Center - m_boundingBoxB.Extents;
	Vector3 bMax = m_boundingBoxB.Center + m_boundingBoxB.Extents;

	// �e���̍������v�Z����
	float dx1 = bMax.x - aMin.x;
	float dx2 = bMin.x - aMax.x;
	float dy1 = bMax.y - aMin.y;
	float dy2 = bMin.y - aMax.y;
	float dz1 = bMax.z - aMin.z;
	float dz2 = bMin.z - aMax.z;

	// �e���ɂ��āA��Βl�̏������������̂߂荞�ݗʂƂ���FAABB�̏d�Ȃ�����������肷��
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// �����߂��x�N�g��
	Vector3 pushBackVec = Vector3::Zero;

	// �߂荞�݂���ԏ��������������߂�
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	// �����߂�
	m_positionA += pushBackVec;
	m_boundingBoxA.Center = m_boundingBoxA.Center + pushBackVec;


	//// �Q�l
	//if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz)){}
	//else if (abs(dy) <= abs(dx) && abs(dy) <= abs(dz)){}
	//else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy)){}
}
