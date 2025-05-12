/*
    �t�@�C�����FPlayerIdling.cpp
    �@�@�@�T�v�F�v���C���[�̑ҋ@��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerIdling.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerIdling::PlayerIdling()
	:
    m_player{}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerIdlingAnimation>();
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
    // �v���C���[���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerIdling::Update()
{
    // �ҋ@����
    Idling();
    // �����Ԃւ̈ڍs����
    TransitionToRunning();
    // �ʏ�U����Ԃւ̈ڍs����
    TransitionToAttackingNormal();

    // �A�j���[�V�������X�V����
    m_animation->Update();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerIdling::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}


//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerIdling::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// �ҋ@����
//---------------------------------------------------------
void PlayerIdling::Idling()
{
    
}

//---------------------------------------------------------
// �����Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerIdling::TransitionToRunning()
{
    // �L�[�{�[�h���͂��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // ���͂�����Α����Ԃֈڍs����
    if (kb->W || kb->S || kb->A || kb->D) // �O
    {
        m_player->ChangeState(m_player->GetPlayerRunning());
    }
}

//---------------------------------------------------------
// �ʏ�U����Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerIdling::TransitionToAttackingNormal()
{
    // �L�[�{�[�h���͂��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    if (kb->F)
    {
        m_player->ChangeState(m_player->GetPlayerAttackingNormal());
    }
}
