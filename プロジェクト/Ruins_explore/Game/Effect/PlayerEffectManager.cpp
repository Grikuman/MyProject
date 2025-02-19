/*
    �t�@�C�����FPlayerEffectManager.cpp
    �@�@�@�T�v�F�v���C���[�̃G�t�F�N�g�N���X���Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Game/Effect/PlayerEffectManager.h"
#include "Game/Player/Player.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerEffectManager::PlayerEffectManager(Player* player)
    :
    m_player{player},
    m_invincibleEffect{}
{
    
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerEffectManager::~PlayerEffectManager()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerEffectManager::Initialize()
{
    // ���G�G�t�F�N�g���쐬����
    m_invincibleEffect = std::make_unique<InvincibleEffect>(m_player);
    // ���G�G�t�F�N�g������������
    m_invincibleEffect->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerEffectManager::Update()
{
    // ���G�G�t�F�N�g���X�V����
    m_invincibleEffect->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerEffectManager::Render()
{
    // ���G�G�t�F�N�g��`�悷��
    m_invincibleEffect->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerEffectManager::Finalize()
{
    m_invincibleEffect->Finalize();
}
