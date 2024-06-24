/*
	@file	Foot.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Foot.h"
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
Foot::Foot()
	:
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_velocity{},
	m_rotate{},
	m_isJumping{},
	m_cameraRotate{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Foot::~Foot()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Foot::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto states = m_commonResources->GetCommonStates();

	//�J�������쐬
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//�����蔻��
	m_collision = std::make_unique<Collision>();
	//�v���C���[���W�̏�����
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
	//�v���C���[�̑��x�̏�����
	m_speed = DirectX::SimpleMath::Vector3::Zero;
	//�J�����̉�]�l�̏�����
	m_cameraRotate = 0.0f;

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerFoot.cmo", *fx);


}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Foot::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // �L�[�{�[�h
    auto gp = m_commonResources->GetInputManager()->GetGamePadState();  // �Q�[���p�b�h
    m_speed = DirectX::SimpleMath::Vector3::Zero;                       // ���x�̃��Z�b�g
    m_world = Matrix::Identity;                                         // �s��̏�����
    m_world *= Matrix::CreateScale(0.004f);
    //*======================================================*
    //�@�L�[�{�[�h���́E�Q�[���p�b�h����
    //�@����:�N�H�[�^�j�I���ł̃v���C���[�����ύX
    //      :�J�����̉�]����
    //*======================================================*

    // ���[���A�s�b�`�A���[
    float roll = 0.0f;  // �y����]
    float pitch = 0.0f; // �w����]
    float yaw = 0.0f;   // �x����]

    float rightX = 0.0f; // yaw�֓n���l
    // �L�[�{�[�h���͂Ɋ�Â��ăv���C���[�̌����ƃJ�����̉�]��ݒ�
    if (kb.Left)
    {
        m_cameraRotate++;
        rightX = 1.0f;
    }
    else if (kb.Right)
    {
        m_cameraRotate--;
        rightX = -1.0f;
    }
    // �R���g���[���[���͂Ɋ�Â��ăv���C���[�̌����ƃJ�����̉�]��ݒ�
    if (gp.IsConnected())
    {
        rightX = -gp.thumbSticks.rightX;
        m_cameraRotate -= gp.thumbSticks.rightX;
    }
    // �Q�[���p�b�h�̓��͂ɂ����yaw��ύX����
    yaw = XMConvertToRadians(rightX * 1.0f); // 1.0f�͓K�؂Ȕ{���ɒ���
    // �N�H�[�^�j�I�������[���A�s�b�`�A���[�̒l���琶������
    Quaternion q = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
    m_rotate = q * m_rotate;

    //*======================================================*
    //�@�L�[�{�[�h���́E�Q�[���p�b�h����
    //�@����:�v���C���[�̑��x�ݒ�ƈړ�
    //*======================================================*
    if (kb.W)
    {
        m_speed.z = -1.f;
    }
    else if (kb.A)
    {
        m_speed.x = -1.f;
    }
    else if (kb.D)
    {
        m_speed.x = 1.f;
    }
    else if (kb.S)
    {
        m_speed.z = 1.f;
    }
    // �R���g���[���[���͂Ɋ�Â��đ��x��ݒ�
    if (gp.IsConnected())
    {
        m_speed.x += gp.thumbSticks.leftX;
        m_speed.z -= gp.thumbSticks.leftY; // ���X�e�B�b�N��Y���͏㉺���]
    }
    //*======================================================*
    //�@�L�[�{�[�h���́E�Q�[���p�b�h����
    //�@����:�v���C���[�̃W�����v
    //*======================================================*
    DirectX::SimpleMath::Vector3 ground(0.f, 0.f, 0.f);
    float gravity = 0.005f;      // �d�͂̋���
    float jumpSpeed = 0.15f;     // �W�����v�̏����x
    float maxFallSpeed = 0.2f;   // �ő嗎�����x

    // �W�����v���Ă��Ȃ���ԂŃW�����v���͂��󂯕t����ƃW�����v�Ɉڍs����
    if (!m_isJumping && kb.Space || !m_isJumping && gp.buttons.a)
    {
        m_velocity.y = jumpSpeed;
        m_isJumping = true;
    }
    if (m_isJumping)
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
    if (m_collision->CheckGround(m_position + DirectX::SimpleMath::Vector3(0.f, 0.0f, 0.f), ground))
    {
        m_position.y = ground.y;
        m_isJumping = false;
        m_velocity.y = 0; // ���x�����Z�b�g
    }

    //*======================================================*
    // ���W�ړ�
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // �Q�[���p�b�h���͂̑��x������0.1�������Ă���
    //�J�����̉�]�s��
    DirectX::SimpleMath::Matrix cameraMatrix;

    cameraMatrix = Matrix::CreateRotationY(XMConvertToRadians(m_cameraRotate));
    //�J�����X�V
    m_camera->Update(m_position, cameraMatrix);
    // ���[���h�s��Ƀ��f���̈ʒu�Ɖ�]�𔽉f������
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Foot::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_camera->GetViewMatrix();
    proj = m_camera->GetProjectionMatrix();
    Matrix projection = m_camera->GetProjectionMatrix();

    // ���f����`�悷��
    m_model->Draw(context, *states, m_world, view, proj);
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Foot::Finalize()
{
}