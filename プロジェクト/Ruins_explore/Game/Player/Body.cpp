/*
	@file	Body.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Body.h"
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
#include "Hand.h"
#include "Foot.h"

#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Body::Body()
	:
    m_commonResources{},
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_velocity{},
	m_rotate{},
	m_cameraRotate{},
    m_hand{},
    m_foot{},
    m_setYaw{},
    m_isAttack{}
{
    m_state = Body::STATE::NONE; // �v���C���[�̏����X�e�[�g
    m_isAttack = false;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Body::~Body()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Body::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//�J�������쐬
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//�����蔻��N���X�𐶐�
	m_collision = std::make_unique<Collision>();
	//�v���C���[���W�̏�����
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerBody.cmo", *fx);

    // �v���C���[�̎���쐬
    m_hand = std::make_unique<Hand>();
    m_hand->Initialize(m_commonResources);
    // �v���C���[�̑����쐬
    m_foot = std::make_unique<Foot>();
    m_foot->Initialize(m_commonResources);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Body::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    m_speed = DirectX::SimpleMath::Vector3::Zero;                       // ���x�̃��Z�b�g
    m_world = Matrix::Identity;                                         // �s��̏�����
    m_world *= Matrix::CreateScale(0.004f);

    //�L�[���́F�R���g���[���[���͂��󂯕t���ē�������߂�
    InputProcessing();
    
    // ���͌�Ɍv�Z�������Ȃ�
    Calculation();

    //�J�����̉�]�s����쐬����
    DirectX::SimpleMath::Matrix cameraMatrix;
    cameraMatrix = Matrix::CreateRotationY(XMConvertToRadians(m_cameraRotate));
    // �J�������X�V����
    m_camera->Update(m_position, cameraMatrix);
    // ��̃p�[�c���X�V����
    m_hand->Update(elapsedTime,m_speed,m_rotate);
    // ���̃p�[�c���X�V����
    m_foot->Update(elapsedTime,m_speed,m_rotate);
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Body::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_camera->GetViewMatrix();
    proj = m_camera->GetProjectionMatrix();

    m_model->Draw(context, *states, m_world, view, proj); // ���f����`�悷��

    m_hand->Render(view,proj);                            // ��p�[�c��`�悷��
    m_foot->Render(view,proj);                            // ���p�[�c��`�悷��
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Body::Finalize()
{
}

//---------------------------------------------------------
// �L�[���́F�R���g���[���[���͂��󂯕t���ē�������߂�
//---------------------------------------------------------
void Body::InputProcessing()
{
    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // �L�[�{�[�h
    m_isAttack = false;
    //*======================================================*
    //�@����:�N�H�[�^�j�I���ł̃v���C���[�����ύX
    //      :�J�����̉�]����
    //*======================================================*

    // ���[���A�s�b�`�A���[
    float roll = 0.0f;  // �y����]
    float pitch = 0.0f; // �w����]
    float yaw = 0.0f;   // �x����]

    m_setYaw = 0.0f; //yaw�ւ̒l��������

    // �L�[�{�[�h���͂Ɋ�Â��ăv���C���[�̌����ƃJ�����̉�]��ݒ�
    if (kb.Left)
    {
        m_cameraRotate++;
        m_setYaw = 1.0f;
    }
    else if (kb.Right)
    {
        m_cameraRotate--;
        m_setYaw = -1.0f;
    }
    // �Q�[���p�b�h�̓��͂ɂ����yaw��ύX����
    yaw = XMConvertToRadians(m_setYaw); // �L�[�{�[�h���Q�[���p�b�h�����l�Ɉ���
    // �N�H�[�^�j�I�������[���A�s�b�`�A���[�̒l���琶������
    Quaternion q = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
    m_rotate = q * m_rotate;

    //*======================================================*
    //�@����:�v���C���[�̑��x�ݒ�ƈړ�
    //*======================================================*
    if (kb.W)
    {
        m_speed.z = -1.f;
    }
    if (kb.A)
    {
        m_speed.x = -1.f;
    }
    if (kb.D)
    {
        m_speed.x = 1.f;
    }
    if (kb.S)
    {
        m_speed.z = 1.f;
    }
    //*======================================================*
    //�@�L�[�{�[�h���́E�Q�[���p�b�h����
    //�@����:�v���C���[�̃W�����v
    //*======================================================*
    DirectX::SimpleMath::Vector3 ground(0.f, 0.f, 0.f);
    float gravity = 0.005f;      // �d�͂̋���
    float jumpSpeed = 0.15f;     // �W�����v�̏����x
    float maxFallSpeed = 0.2f;   // �ő嗎�����x

    Vector3 oldpos = m_position; //�W�����v�O�̈ʒu��ۑ����Ă���

    // �W�����v���Ă��Ȃ���ԂŃW�����v���͂��󂯕t����ƃW�����v�Ɉڍs����
    if (m_state == STATE::NONE && kb.Space)
    {
        m_velocity.y = jumpSpeed;      // �����x��������
        m_state = STATE::JUMPING;      // �W�����v���ɂ���
        m_hand->OnJumpTrigger();       // ��p�[�c���W�����v������
        m_foot->OnJumpTrigger();       // ���p�[�c���W�����v������
    }
    //�W�����v���̏���
    if (m_state == STATE::JUMPING)
    {
        // �W�����v���x�ɏd�͂�K�p
        m_velocity.y -= gravity;

        // �������x���ő嗎�����x�𒴂��Ȃ��悤�ɂ���
        if (m_velocity.y < -maxFallSpeed)
        {
            m_velocity.y = -maxFallSpeed;
        }
        // �ʒu���X�V
        m_position.y += m_velocity.y;
    }
    // �n�ʂƂ̏Փ˂��`�F�b�N
    if (m_collision->CheckGround(
        m_position - DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f),
        ground))
    {
        m_position = oldpos; // �W�����v�O�̈ʒu�ɖ߂�
        m_state = STATE::NONE; // �W�����v���ł͂Ȃ��Ȃ�
        m_velocity.y = 0; // ���x�����Z�b�g
    }
    // 
    if (m_hand->GetState() == Hand::STATE::ATTACKING)
    {
        m_isAttack = true;
    }
}

//---------------------------------------------------------
// ���͌�Ɍv�Z�������Ȃ�
//---------------------------------------------------------
void Body::Calculation()
{
    // ���W�ړ�
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // �Q�[���p�b�h���͂̑��x������0.1�������Ă���
    // ���[���h�s��Ƀ��f���̈ʒu�Ɖ�]�𔽉f������
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

DirectX::BoundingSphere Body::GetBoundingSphere()
{
    Vector3 center = m_position; // �����蔻�苅�̒��S
    float radius = 0.5f;         // �G�̃T�C�Y�ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}
