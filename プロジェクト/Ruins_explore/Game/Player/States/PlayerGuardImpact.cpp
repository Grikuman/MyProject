/*
    �t�@�C�����FPlayerGuarding.cpp
    �@�@�@�T�v�F�v���C���[�̕��s��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerGuarding.h"
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
PlayerGuarding::PlayerGuarding()
	:
    m_player{}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<PlayerGuardingAnimation>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerGuarding::~PlayerGuarding()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerGuarding::Initialize()
{
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerGuarding::Update()
{
    // �A�j���[�V�������X�V����
    m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerGuarding::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerGuarding::Finalize()
{
    m_animation->Finalize();
}
