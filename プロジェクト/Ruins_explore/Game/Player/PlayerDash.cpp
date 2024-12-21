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

using namespace DirectX;
using namespace DirectX::SimpleMath;

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

    
    // �v���C���[����
    PlayerInput();

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
// �v���C���[����
//---------------------------------------------------------
void PlayerDash::PlayerInput()
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // �v���C���[����
    if (kb->A)
    {
        m_player->SetAngle(m_player->GetAngle() + 3.0f); // ��]
    }
    if (kb->D)
    {
        m_player->SetAngle(m_player->GetAngle() - 3.0f); // ��]
    }
}

//---------------------------------------------------------
// �_�b�V������
//---------------------------------------------------------
void PlayerDash::Dash()
{
    // �^�������i��
    m_player->SetVelocity(Vector3::Forward * 4.f);
    // �_�b�V�����Ԃ�����������
    m_dashTime--;

    // �_�b�V�����Ԃ��I�������ꍇ
    if (m_dashTime <= 0.f)
    {
        // �_�b�V�����Ԃ����Z�b�g����
        m_dashTime = DASHTIME;
        // �A�C�h�����O��Ԃֈڍs����
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}
