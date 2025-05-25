/*
    �t�@�C�����FPlayerGuardImpact.cpp
    �@�@�@�T�v�F�v���C���[�̃K�[�h�Ռ���Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerGuardImpact.h"
#include "Game/Player/Player.h"
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
PlayerGuardImpact::PlayerGuardImpact()
	:
    m_player{}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerGuardImpactAnimation>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerGuardImpact::~PlayerGuardImpact()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerGuardImpact::Initialize()
{
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerGuardImpact::Update()
{
    // �A�j���[�V�������X�V����
    m_animation->Update();

    // �ҋ@��Ԃւ̈ڍs����
    TransitionToIdling();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerGuardImpact::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}


//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerGuardImpact::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// �ҋ@��Ԃւ̈ڍs����
//---------------------------------------------------------
void PlayerGuardImpact::TransitionToIdling()
{
    if (m_animation->IsEndAnimation())
    {
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}
