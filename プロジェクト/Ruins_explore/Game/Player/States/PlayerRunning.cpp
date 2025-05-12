/*
    �t�@�C�����FPlayerRunning.cpp
    �@�@�@�T�v�F�v���C���[�̑����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerRunning.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerRunning::PlayerRunning()
	:
    m_player{}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerRunningAnimation>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerRunning::~PlayerRunning()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerRunning::Initialize()
{
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerRunning::Update()
{
    // ���鏈��
    Running();
    // �ҋ@��Ԃւ̈ڍs����
    TransitionToIdling();
    // �����Ԃւ̈ڍs����
    TransitionToRolling();
    // �ʏ�U����Ԃւ̈ڍs����
    TransitionToAttackingNormal();
    // �����̏���
    Direction();

    // �A�j���[�V�������X�V����
    m_animation->Update();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerRunning::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}


//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerRunning::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// ���鏈��
//---------------------------------------------------------
void PlayerRunning::Running()
{
    using namespace DirectX::SimpleMath;
    // �L�[�{�[�h���͂��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // ���͕������擾���āA�����ɉ����Ĉړ�����
    if (kb->W) // �O
    {
        m_player->SetVelocity(Vector3::Forward);
    }
    if (kb->S) // ��
    {
        m_player->SetVelocity(Vector3::Backward);
    }
    if (kb->A) // ��
    {
        m_player->SetVelocity(Vector3::Left);
    }
    if (kb->D) // �E
    {
        m_player->SetVelocity(Vector3::Right);
    }

    // �ړ����x��␳
    m_player->ApplyVelocity(APPLY_VELOCITY);
    // �ړ�������
    m_player->SetPosition(m_player->GetPosition() + DirectX::SimpleMath::Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// �ҋ@��Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerRunning::TransitionToIdling()
{
    // �L�[�{�[�h���͂��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();
    // ���͂�������Αҋ@��Ԃֈڍs����
    if (kb->W || kb->S || kb->A || kb->D)
    {
        return;
    }
    m_player->ChangeState(m_player->GetPlayerIdling());
}

//---------------------------------------------------------
// �����Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerRunning::TransitionToRolling()
{
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // �X�^�~�i������ꍇ
    if (m_player->GetStamina() >= 1)
    {
        // �X�y�[�X�L�[����������
        if (kb->Space)
        {
            // �X�^�~�i�������
            m_player->SetStamina(m_player->GetStamina() - 1);
            // �_�b�V����
            Audio::GetInstance()->PlaySE("DashSE");
            // �����ԂɕύX����
            m_player->ChangeState(m_player->GetPlayerRolling());
        }
    }
}

//---------------------------------------------------------
// �ʏ�U����Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerRunning::TransitionToAttackingNormal()
{
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    if (kb->F)
    {
        m_player->ChangeState(m_player->GetPlayerAttackingNormal());
    }
}

//---------------------------------------------------------
// �����̏���
//---------------------------------------------------------
void PlayerRunning::Direction()
{
    using namespace DirectX::SimpleMath;
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // ���͕������擾���āA������ݒ肷��
    if (kb->W) // �O
    {
        m_player->SetDirection(Vector3::Forward);
    }
    if (kb->S) // ��
    {
        m_player->SetDirection(Vector3::Backward);
    }
    if (kb->A) // ��
    {
        m_player->SetDirection(Vector3::Left);
    }
    if (kb->D) // �E
    {
        m_player->SetDirection(Vector3::Right);
    }
}
