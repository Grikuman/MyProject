/*
    �t�@�C�����FPlayerDash.cpp
    �@�@�@�T�v�F�v���C���[�̃_�b�V����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerDash.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerDash::PlayerDash(Player* player)
	:
    m_player(player),
	m_model{},
    m_dashTime{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerDash::~PlayerDash()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerDash::Initialize()
{
    // ���f�����擾����
    m_model = Resources::GetInstance()->GetModel(L"Player");
    // �_�b�V�����Ԃ�ݒ�
    m_dashTime = DASHTIME;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerDash::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // �_�b�V������
    Dash();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerDash::Render()
{
   
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerDash::Finalize()
{
    
}

//---------------------------------------------------------
// �_�b�V������
//---------------------------------------------------------
void PlayerDash::Dash()
{
    using namespace DirectX::SimpleMath;
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // �v���C���[����
    if (kb->A || kb->Left)
    {
        // Y���𒆐S�ɍ���]�����Z
        Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(3.0f));
        m_player->AddAngle(rotation);
    }
    if (kb->D || kb->Right)
    {
        // Y���𒆐S�ɉE��]�����Z
        Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(-3.0f));
        m_player->AddAngle(rotation);
    }

    // ���݂̊p�x���擾
    Quaternion angle = m_player->GetAngle(); 
    angle.Normalize(); 
    // ���K����̊p�x��ݒ�
    m_player->SetAngle(angle); 

    // �ړ�����
    m_player->AddVelocity(Vector3::Forward * 4.0f);
    // �ړ����x��␳
    m_player->ApplyVelocity(0.05f);

    // �N�H�[�^�j�I����p���Ĉړ�
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));

    // �_�b�V��������s��
    DashToWalk();
}

//---------------------------------------------------------
// �_�b�V��������s��
//---------------------------------------------------------
void PlayerDash::DashToWalk()
{
    // �_�b�V�����Ԃ̊Ǘ�
    m_dashTime--;
    if (m_dashTime <= 0.f)
    {
        m_dashTime = DASHTIME;
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}

//---------------------------------------------------------
// �_�b�V������U����
//---------------------------------------------------------
void PlayerDash::DashToAttack()
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    if (kb->F)
    {
        // �U���ֈڍs����
        m_player->ChangeState(m_player->GetPlayerAttack());
    }
}

//using namespace DirectX::SimpleMath;
//auto kb = InputDevice::GetInstance()->GetKeyboardState();
//
//// �v���C���[����
//if (kb->A || kb->Left)
//{
//    m_player->AddRotation(3.0f); // ��]
//}
//if (kb->D || kb->Right)
//{
//    m_player->AddRotation(-3.0f); // ��]
//}
//
//// �^�������i��
//m_player->AddVelocity(Vector3::Forward * 4.f);
//// �_�b�V�����Ԃ�����������
//m_dashTime--;
//
//// �_�b�V�����Ԃ��I�������ꍇ
//if (m_dashTime <= 0.f)
//{
//    // �_�b�V�����Ԃ����Z�b�g����
//    m_dashTime = DASHTIME;
//    // �A�C�h�����O��Ԃֈڍs����
//    m_player->ChangeState(m_player->GetPlayerWalk());
//}
//
//// �ړ����x��␳
//m_player->ApplyVelocity(0.05f);
//
//// �N�H�[�^�j�I����p���Ĉړ�
//m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));