/*
    �t�@�C�����FPlayerWalk.cpp
    �@�@�@�T�v�F�v���C���[�̕��s��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerWalk.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerWalk::PlayerWalk(Player* player)
	:
    m_player(player),
	m_model{},
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
    // ���s����W�����v��
    WalkToJump();
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

void PlayerWalk::WalkToJump()
{
    // �L�[�{�[�h�̏�Ԃ��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();
    if (kb->G)
    {
        m_player->ChangeState(m_player->GetPlayerJump());
    }
}
