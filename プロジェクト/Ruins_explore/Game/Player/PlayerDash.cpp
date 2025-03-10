/*
    �t�@�C�����FPlayerDash.cpp
    �@�@�@�T�v�F�v���C���[�̃_�b�V����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerDash.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerDash::PlayerDash(Player* player)
	:
    m_player(player),
    m_nowDirection{DirectX::SimpleMath::Vector3::Backward},
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
    // �_�b�V�����Ԃ�ݒ�
    m_dashTime = DASHTIME;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerDash::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // �_�b�V������
    Dash();
    // �_�b�V��������s��
    DashToWalk(); 
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
    // �ړ�����(���͕����ɓ���)
    m_player->AddVelocity(m_nowDirection * 4.0f);
    // �ړ����x��␳
    m_player->ApplyVelocity(0.05f);
    // �N�H�[�^�j�I����p���Ĉړ�
    m_player->SetPosition(m_player->GetPosition() + DirectX::SimpleMath::Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// �_�b�V��������s��
//---------------------------------------------------------
void PlayerDash::DashToWalk()
{
    // �_�b�V�����Ԃ̊Ǘ�
    m_dashTime--;
    if (m_dashTime <= 0.0f)
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