/*
    @file    PlayerStatusUI.cpp
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerStatusUI.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "PlayerUIManager.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerStatusUI::PlayerStatusUI(Player* player)
    :
    m_player{player},
    m_spriteBatch{},
    m_healthPosition{},
    m_staminaPosition{},
    m_scale{1.f},
    m_hearthRed_Tex{},
    m_hearthGray_Tex{},
    m_staminaYellow_Tex{},
    m_staminaGray_Tex{},
    m_statusIcon_Tex{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerStatusUI::~PlayerStatusUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerStatusUI::Initialize()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // �X�v���C�g�o�b�`���擾����
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    // �摜��ǂݍ���
    m_statusIcon_Tex    = Resources::GetInstance()->GetTexture(L"StatusIcon");
    m_hearthRed_Tex     = Resources::GetInstance()->GetTexture(L"HealthRed");
    m_hearthGray_Tex    = Resources::GetInstance()->GetTexture(L"HealthGray");
    m_staminaYellow_Tex = Resources::GetInstance()->GetTexture(L"StaminaYellow");
    m_staminaGray_Tex   = Resources::GetInstance()->GetTexture(L"StaminaGray");

    // �̗͕\���̈ʒu��ݒ肷��
    for (int i = 0; i < m_player->GetMAXHP(); i++)
    {
        m_healthPosition[i] = Vector2(HEALTH_SHIFT_LENGTH * i + HEALTH_POS_ORIGIN.x, HEALTH_POS_ORIGIN.y);
    }
    // �X�^�~�i�\���̈ʒu��ݒ肷��
    for (int i = 0; i < m_player->GetMAXSTAMINA(); i++)
    {
        m_staminaPosition[i] = Vector2(STAMINA_SHIFT_LENGTH * i + STAMINA_POS_ORIGIN.x, STAMINA_POS_ORIGIN.y);
    }
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerStatusUI::Update()
{
    // ���݂�HP�������v�Z
    m_scale = static_cast<float>(m_player->GetHP() / m_player->GetMAXHP());
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerStatusUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();
    // �X�e�[�^�X�A�C�R��
    m_spriteBatch->Draw(m_statusIcon_Tex.Get(), STATUS_ICON_POS);
    // �̗�(�D�F)
    for (int i = 0; i < m_player->GetMAXHP(); i++)
    {
        m_spriteBatch->Draw(m_hearthGray_Tex.Get(), m_healthPosition[i]);
    }
    // �̗�(�ԐF)
    for (int i = 0; i < m_player->GetHP(); i++)
    {
        m_spriteBatch->Draw(m_hearthRed_Tex.Get(), m_healthPosition[i]);
    }
    // �X�^�~�i(�D�F)
    for (int i = 0; i < m_player->GetMAXSTAMINA(); i++)
    {
        m_spriteBatch->Draw(m_staminaGray_Tex.Get(), m_staminaPosition[i]);
    }
    // �X�^�~�i(���F)
    for (int i = 0; i < m_player->GetStamina(); i++)
    {
        m_spriteBatch->Draw(m_staminaYellow_Tex.Get(), m_staminaPosition[i]);
    }
    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerStatusUI::Finalize()
{
   
}