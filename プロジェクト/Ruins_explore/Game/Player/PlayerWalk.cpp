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
    
    // ���s����
    PlayerMove();
    // ���s����_�b�V����
    WalkToDash();
    // ���s����U����
    WalkToAttack();
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
// ���s����
//---------------------------------------------------------
void PlayerWalk::PlayerMove()
{
    using namespace DirectX::SimpleMath;
    // �L�[�{�[�h���͂��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // �ړ�����
    if (kb->W || kb->Up)
    {
        m_player->AddVelocity(Vector3::Forward);
    }
    if (kb->S || kb->Down)
    {
        m_player->AddVelocity(Vector3::Backward);
    }

    // ��]����
    if (kb->A || kb->Left)
    {
        m_player->AddRotation(2.0f);  // ����]
    }
    if (kb->D || kb->Right)
    {
        m_player->AddRotation(-2.0f); // �E��]
    }

    // �ړ����x��␳
    m_player->ApplyVelocity(0.05f);

    // �N�H�[�^�j�I����p���Ĉړ�
    Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(m_player->GetAngle()));
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), rotation));
}

//---------------------------------------------------------
// ���s����_�b�V����
//---------------------------------------------------------
void PlayerWalk::WalkToDash()
{
    // �L�[�{�[�h���擾����
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // �X�^�~�i������ꍇ
    if (m_player->GetStamina() >= 1)
    {
        // �X�y�[�X�L�[����������
        if (dashkb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            // �X�^�~�i�������
            m_player->SetStamina(m_player->GetStamina() - 1);
            // �X�e�[�g���_�b�V���ɕύX����
            m_player->ChangeState(m_player->GetPlayerDash());
        }
    }
}

//---------------------------------------------------------
// ���s����U����
//---------------------------------------------------------
void PlayerWalk::WalkToAttack()
{
    // �L�[�{�[�h���擾����
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // F�L�[����������
    if (dashkb->IsKeyPressed(DirectX::Keyboard::F))
    {
        // �X�e�[�g���U���ɕύX����
        m_player->ChangeState(m_player->GetPlayerAttack());
    }
}
