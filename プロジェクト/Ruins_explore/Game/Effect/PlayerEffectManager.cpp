#pragma once
#include "pch.h"
#include "Game/Effect/PlayerEffectManager.h"
#include "Game/CommonResources.h"
#include "Game/Player/Player.h"

// �R���X�g���N�^
PlayerEffectManager::PlayerEffectManager(Player* player)
    :
    m_commonResources{},
    m_player{player},
    m_invincibleEffect{}
{
    
}
// �f�X�g���N�^
PlayerEffectManager::~PlayerEffectManager()
{

}

// ������
void PlayerEffectManager::Initialize(CommonResources* resources)
{
    m_commonResources = resources;

    // ���G�G�t�F�N�g���쐬����
    m_invincibleEffect = std::make_unique<InvincibleEffect>(m_player);
    // ���G�G�t�F�N�g������������
    m_invincibleEffect->Initialize(resources);
}

// �X�V����
void PlayerEffectManager::Update()
{
    m_invincibleEffect->Update();
}

// �`�悷��
void PlayerEffectManager::Render()
{
    m_invincibleEffect->Render();
}

// �㏈������
void PlayerEffectManager::Finalize()
{
    m_invincibleEffect->Finalize();
}
