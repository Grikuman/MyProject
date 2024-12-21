/*
    �t�@�C�����FPlayerWalk.cpp
    �@�@�@�T�v�F�v���C���[�̕��s��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerWalk.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerWalk::PlayerWalk(Player* player)
	:
    m_player(player),
	m_model{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerWalk::~PlayerWalk()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerWalk::Initialize()
{
    // ���f�����擾����
    m_model = Resources::GetInstance()->GetModel(L"Player");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerWalk::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    
    // �v���C���[����
    PlayerMove();

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
void PlayerWalk::Render()
{
    
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerWalk::Finalize()
{
    
}

//---------------------------------------------------------
// �v���C���[����
//---------------------------------------------------------
void PlayerWalk::PlayerMove()
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
