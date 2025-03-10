/*
    �t�@�C�����FPlayerWalk.cpp
    �@�@�@�T�v�F�v���C���[�̕��s��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerWalk.h"
#include "PlayerDash.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"
#include "Game/Camera/TPS_Camera.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerWalk::PlayerWalk(Player* player)
	:
    m_player(player),
    m_keyHoldTime{}
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
    if(kb->A || kb->Left)
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

    // �ړ����x��␳
    m_player->ApplyVelocity(0.05f);

    // �ړ�������
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// ���s����_�b�V����
//---------------------------------------------------------
void PlayerWalk::WalkToDash()
{
    // �L�[�{�[�h���擾����
    auto dashKb = InputDevice::GetInstance()->GetKeyboardStateTracker();
    // �_�b�V�������p�̃L�[�{�[�h���擾����
    auto directionKb = InputDevice::GetInstance()->GetKeyboardState();
    // �_�b�V��������ݒ肷��
    if (directionKb->W || directionKb->Up)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Forward);
    }
    if (directionKb->S || directionKb->Down)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Backward); 
    }
    if (directionKb->D || directionKb->Right)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Right); 
    }
    if (directionKb->A || directionKb->Left)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Left); 
    }

    // �X�^�~�i������ꍇ
    if (m_player->GetStamina() >= 1)
    {
        // �X�y�[�X�L�[����������
        if (dashKb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            // �X�^�~�i�������
            m_player->SetStamina(m_player->GetStamina() - 1);
            // �X�e�[�g���_�b�V���ɕύX����
            m_player->ChangeState(m_player->GetPlayerDash());
            // �_�b�V����
            Audio::GetInstance()->PlaySE("DashSE");
        }
    }
}

//---------------------------------------------------------
// ���s����U����
//---------------------------------------------------------
void PlayerWalk::WalkToAttack()
{
    // �L�[�{�[�h�̏�Ԃ��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // F�L�[��������Ă��邩���m�F
    if (kb->IsKeyDown(DirectX::Keyboard::F))
    {
        // �ʏ�p���`�ɐݒ肷��
        m_player->GetPlayerAttack()->ChangeAttackAction(
            m_player->GetPlayerAttack()->GetPlayerNormalPunch());
        // �U���ֈڍs����
        m_player->ChangeState(m_player->GetPlayerAttack());
        // �p���`��
        Audio::GetInstance()->PlaySE("PunchSE");
        // �J������h�炷
        m_player->GetCamera()->StartShake(0.1f, 0.05f);
    }

    // C�L�[��������Ă��邩���m�F
    if (kb->IsKeyDown(DirectX::Keyboard::C))
    {
        // �������J�E���g�𑝉�
        m_keyHoldTime++;

        // ������������̎��ԁi�t���[�����j�𒴂����ꍇ
        if (m_keyHoldTime > 30) // 30�t���[���ȏ�
        {
            // �`���[�W�p���`�ɂȂ��Ă��Ȃ����
            if (m_player->GetPlayerAttack()->GetCurrentAttackAction() != m_player->GetPlayerAttack()->GetPlayerChargePunch())
            {
                // �`���[�W�p���`�ɕύX
                m_player->GetPlayerAttack()->ChangeAttackAction(m_player->GetPlayerAttack()->GetPlayerChargePunch());
            }
            // �U���ֈڍs����
            m_player->ChangeState(m_player->GetPlayerAttack());
            // �p���`��
            Audio::GetInstance()->PlaySE("PunchSE");
            // ���������Ԃ�0��
            m_keyHoldTime = 0;
        }
    }
    else
    {
        // C�L�[�������ꂽ�璷�����J�E���g�����Z�b�g
        m_keyHoldTime = 0;
    }
}
