/*
	@file	Hand.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Hand.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <GeometricPrimitive.h>
#include <iostream>
#include "Libraries/MyLib/GridFloor.h"
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Hand::Hand()
	:
	m_commonResources{},
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_jumpSpeed{},
	m_rotate{},
	m_isJumping{},
	m_jumpTrigger{},
	m_cameraRotate{}
{
	m_state = Hand::STATE::NONE;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Hand::~Hand()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Hand::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//�J�������쐬
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//�����蔻��
	m_collision = std::make_unique<Collision>();
	//�v���C���[���W�̏�����
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
	//�v���C���[�̑��x�̏�����
	m_speed = DirectX::SimpleMath::Vector3::Zero;
	// �W�����v�g���K�[��������
	m_jumpTrigger = false;
	//�J�����̉�]�l�̏�����
	m_cameraRotate = 0.0f;

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerHand.cmo", *fx);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Hand::Update(
	float elapsedTime,
	DirectX::SimpleMath::Vector3 speed,
	DirectX::SimpleMath::Quaternion rotate
)
{
    UNREFERENCED_PARAMETER(elapsedTime);
	m_speed = speed;
    m_world = Matrix::Identity;                                         // �s��̏�����
    m_world *= Matrix::CreateScale(0.004f);
	m_state = Hand::STATE::NONE;

	// Body�̃N�H�[�^�j�I������荞��
	m_rotate = rotate;  

	// �W�����v
	Jump();

    // ���W�ړ�
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // �Q�[���p�b�h���͂̑��x������0.1�������Ă���

	auto kb = m_commonResources->GetInputManager()->GetKeyboardState();
	float r = 0;
	if (kb.F)
	{
		r = 45.f;
		m_state = Hand::STATE::ATTACKING;
	}
	m_world *= Matrix::CreateRotationY(XMConvertToRadians(r));

    // ���[���h�s��Ƀ��f���̈ʒu�Ɖ�]�𔽉f������
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Hand::Render(
	DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix proj)
{
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates(); 

    // ���f����`�悷��
    m_model->Draw(context, *states, m_world, view, proj);
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Hand::Finalize()
{
}

void Hand::OnJumpTrigger()
{
	m_jumpTrigger = true;
}

void Hand::Jump()
{
	DirectX::SimpleMath::Vector3 ground(0.f, 0.f, 0.f);
	float gravity = 0.005f;      // �d�͂̋���
	float jumpSpeed = 0.15f;     // �W�����v�̏����x
	float maxFallSpeed = 0.2f;   // �ő嗎�����x

	Vector3 oldpos = m_position; //�W�����v�O�̈ʒu

	// �W�����v���Ă��Ȃ���Ԃ��g���K�[��TRUE�Ȃ�W�����v�Ɉڍs����
	if (!m_isJumping && m_jumpTrigger)// || !m_isJumping && gp.buttons.a)
	{
		m_jumpSpeed.y = jumpSpeed;
		m_isJumping = true; // �W�����v���ɂ���
	}
	if (m_isJumping)
	{
		// �W�����v���x�ɏd�͂�K�p
		m_jumpSpeed.y -= gravity;

		// �������x���ő嗎�����x�𒴂��Ȃ��悤�ɂ���
		if (m_jumpSpeed.y < -maxFallSpeed)
		{
			m_jumpSpeed.y = -maxFallSpeed;
		}

		// �ʒu���X�V
		m_position.y += m_jumpSpeed.y;
	}
	// �n�ʂƂ̏Փ˂��`�F�b�N
	if (m_collision->CheckGround(
		m_position - DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f),
		ground))
	{
		m_position = oldpos; // �W�����v�O�̈ʒu�ɖ߂�
		m_isJumping = false; // �W�����v���\�ɂ�����
		m_jumpTrigger = false; //�g���K�[��߂�
		m_jumpSpeed.y = 0; // ���x�����Z�b�g
	}
}