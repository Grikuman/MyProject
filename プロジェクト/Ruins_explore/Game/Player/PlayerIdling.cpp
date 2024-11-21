/*
    �t�@�C��: PlayerIdling.cpp
    �N���X  : �v���C���[�A�C�h�����O�N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerIdling.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerIdling::PlayerIdling(Player* player)
	:
    m_player(player),
	m_model{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerIdling::~PlayerIdling()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerIdling::Initialize()
{
    // ���f�����擾����
    m_model = Resources::GetInstance()->GetModel(L"Player");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerIdling::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    
    // �v���C���[����
    PlayerInput();

    // �L�[�{�[�h���擾����
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // �X�^�~�i������ꍇ
    if (m_player->GetStamina() >= 1)
    {
        // �X�y�[�X�L�[����������
        if (dashkb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            m_player->SetStamina(m_player->GetStamina() - 1); // �X�^�~�i������
            m_player->ChangeState(m_player->GetPlayerDash()); // �X�e�[�g���_�b�V���ɕύX
        }
    }
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerIdling::Render()
{
    
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerIdling::Finalize()
{
    
}

//---------------------------------------------------------
// �v���C���[����
//---------------------------------------------------------
void PlayerIdling::PlayerInput()
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();
    if (kb->W)
    {
        m_player->SetVelocity(Vector3::Forward);         // �ړ�
    }
    if (kb->A)
    {
        m_player->SetAngle(m_player->GetAngle() + 2.0f); // ��]
    }
    if (kb->S)
    {
        m_player->SetVelocity(Vector3::Backward);        // �ړ�
    }
    if (kb->D)
    {
        m_player->SetAngle(m_player->GetAngle() - 2.0f); // ��]
    }
    if (kb->Up)
    {
        m_player->SetVelocity(Vector3::Forward);         // �ړ�
    }
    if (kb->Left)
    {
        m_player->SetAngle(m_player->GetAngle() + 2.0f); // ��]
    }
    if (kb->Down)
    {
        m_player->SetVelocity(Vector3::Backward);        // �ړ�
    }
    if (kb->Right)
    {
        m_player->SetAngle(m_player->GetAngle() - 2.0f); // ��]
    }
}
