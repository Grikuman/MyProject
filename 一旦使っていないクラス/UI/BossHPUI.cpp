/*
    �t�@�C�����FBossHPUI.h
    �@�@�@�T�v�F�{�X�̗̑�UI���Ǘ�����N���X
*/

#include "pch.h"
#include "BossHPUI.h"
#include "UserInterface.h"
#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include <vector>
#include <string>

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
BossHPUI::BossHPUI()
    : m_menuIndex(0)
    ,m_windowHeight(0)
    ,m_windowWidth(0)
    ,m_pDR(nullptr)
    ,m_baseTexturePath(nullptr)
    ,m_BossHPUI(nullptr)
    ,m_frame(nullptr)
    ,m_spriteBatch{}
    ,m_spriteFont{}
    ,m_currentHP{}
    ,m_maxHP{}
{
    
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
BossHPUI::~BossHPUI()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void BossHPUI::Initialize(DX::DeviceResources* pDR,int width,int height)
{
    // �f�o�C�X�E��ʃT�C�Y��ݒ�
	m_pDR = pDR;
    m_windowWidth = width;
    m_windowHeight = height;
    // �̗̓Q�[�W(��)�̃p�X���w�肷��
    m_baseTexturePath = L"Resources/Textures/HP.jpg";
    // �e�N�X�`��
    Add(L"Resources/Textures/HP_red.jpg"
        , DirectX::SimpleMath::Vector2(width / 2, 50.0f)
        , DirectX::SimpleMath::Vector2(1.0f,1.0f)
        , UserInterface::MIDDLE_CENTER);
    // �X�v���C�g�o�b�`
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    // �X�v���C�g�t�H���g
    m_spriteFont = Graphics::GetInstance()->GetFont();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void BossHPUI::Update(float bossHP,float MAX_BossHP)
{
    m_currentHP = bossHP;
    m_maxHP = MAX_BossHP;
    // �䗦
    float ratio;
    // ���݂̗̑͊������v�Z����
    ratio = m_currentHP / m_maxHP;
    // �䗦��ݒ肷��
    m_BossHPUI->SetRenderRatio(ratio);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void BossHPUI::Render()
{
    // �e�e�N�X�`����`�悷��
    m_base->Render();
    m_BossHPUI->Render();
    // �X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();
    // �{�X��
    m_spriteFont->DrawString(m_spriteBatch, L"BOSS", DirectX::SimpleMath::Vector2(610,2));
    // �{�X�̗̑͊�����\������
    m_spriteFont->DrawString(
        m_spriteBatch,
        (std::to_wstring(static_cast<int>(m_currentHP)) + L"/" + std::to_wstring(static_cast<int>(m_maxHP))).c_str(),
        DirectX::SimpleMath::Vector2(597, 32)
    );
    // �X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// �ǉ�����
//---------------------------------------------------------
void BossHPUI::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
{
    // �̗̓Q�[�W(�ԐF)���쐬����
    m_base = std::make_unique<UserInterface>();
    m_base->Create(m_pDR
        , L"Resources/Textures/HP_red.jpg"
        , position
        , scale
        , anchor);
    m_base->SetWindowSize(m_windowWidth, m_windowHeight);

    // �̗̓Q�[�W(�ΐF)���쐬����
    m_BossHPUI = std::make_unique<UserInterface>();
    m_BossHPUI->Create(m_pDR
        , m_baseTexturePath
        , position
        , scale
        , anchor);
    m_BossHPUI->SetWindowSize(m_windowWidth, m_windowHeight);
    m_BossHPUI->SetRenderRatioOffset(0.f);
    //m_BossHPUI->SetRenderRatioOffset(0.3f);

    // �̗̓Q�[�W�̘g���쐬����
    m_frame = std::make_unique<UserInterface>();
    m_frame->Create(m_pDR
        , path
        , position + DirectX::SimpleMath::Vector2(0.f, 5.f)
        , scale
        , anchor);
    m_frame->SetWindowSize(m_windowWidth, m_windowHeight);
}


