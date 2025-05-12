/*
    �t�@�C�����FPlayerRolling.cpp
    �@�@�@�T�v�F�v���C���[�̉����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerRolling.h"
#include "Game/Player/Player.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerRolling::PlayerRolling()
	:
    m_player{}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerRollingAnimation>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerRolling::~PlayerRolling()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerRolling::Initialize()
{
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerRolling::Update()
{
    // �������
    Rolling();
    // �ҋ@��Ԃւ̈ڍs����
    TransitionToIdling();

    // �A�j���[�V�������X�V����
    m_animation->Update();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerRolling::Render()
{
   // �A�j���[�V������`�悷��
    m_animation->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerRolling::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// �������
//---------------------------------------------------------
void PlayerRolling::Rolling()
{
    // �������擾����
    DirectX::SimpleMath::Vector3 direction = m_player->GetDirection();
    // �ړ����x��ݒ肷��
    m_player->SetVelocity(direction);
    // �ړ����x��␳����
    m_player->ApplyVelocity(APPLY_VELOCITY);
    // �ړ�����
    m_player->SetPosition(m_player->GetPosition() + DirectX::SimpleMath::Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// �ҋ@��Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerRolling::TransitionToIdling()
{
    // �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
    if (m_animation->IsEndAnimation())
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}