/*
    �t�@�C�����FPlayerAttackingNormal.cpp
    �@�@�@�T�v�F�v���C���[�̒ʏ�U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerAttackingNormal.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �U���͈͂��擾����
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttackingNormal::GetAttackRange()
{
    return DirectX::BoundingSphere(m_player->GetPosition(), ATTACK_DISTANCE);
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerAttackingNormal::PlayerAttackingNormal(Player* player)
	:
    m_player{player}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerAttackingNormalAnimation>(player);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerAttackingNormal::~PlayerAttackingNormal()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerAttackingNormal::Initialize()
{
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerAttackingNormal::Update()
{
    // �ҋ@��Ԃւ̈ڍs����
    TransitionToIdling();
    // �A�j���[�V�������X�V����
    m_animation->Update();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttackingNormal::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}


//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerAttackingNormal::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// �ҋ@��Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerAttackingNormal::TransitionToIdling()
{
    if (m_animation->IsEndAnimation())
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}

