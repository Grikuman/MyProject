/*
    �t�@�C�����FPlayerRolling.cpp
    �@�@�@�T�v�F�v���C���[�̃_�b�V����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerRolling.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerRolling::PlayerRolling(Player* player)
	:
    m_player{player}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerRollingAnimation>(player);
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
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerRolling::Update(const float& elapsedTime)
{
    // �������
    Rolling();
    // �ҋ@��Ԃւ̈ڍs����
    TransitionToIdling();

    // �A�j���[�V�������X�V����
    m_animation->Update(elapsedTime);
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
// ��n������
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
    m_player->ApplyVelocity(0.1f);
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