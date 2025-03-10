/*
    �t�@�C�����FTitleSceneUI.cpp
    �@�@�@�T�v�F�^�C�g���V�[����UI���Ǘ�����N���X
*/
#include "pch.h"
#include "TitleSceneUI.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Game/Scene/TitleScene.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI(TitleScene* titlescene)
    :
    m_spriteBatch{},
    m_gameTitle_Tex{},
    m_select_Tex{},
    m_selectArrow_Tex{},
    m_i_Tex{},
    m_o_Tex{},
    m_backGround_Tex{},
    m_selectFlag{true},
    m_titleScene{titlescene},
    m_rotate{},
    m_selectArrowPos{}
{
    // �X�v���C�g�o�b�`���擾����
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TitleSceneUI::~TitleSceneUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TitleSceneUI::Initialize()
{
    // �摜�ǂݍ���
    m_gameTitle_Tex   = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Ruins_Explorer.png");
    m_select_Tex      = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/TitleSelect.png");
    m_selectArrow_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/SelectArrow.png");
    m_i_Tex           = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/i.png");
    m_o_Tex           = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/o.png");
    m_backGround_Tex  = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/TitleBackGround.png");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // ������]
    m_rotate += 1.f;

    // ��L�[����������
    if (kb->IsKeyPressed(DirectX::Keyboard::Up))
    {
        m_selectFlag = true;
    }
    // ���L�[����������
    if (kb->IsKeyPressed(DirectX::Keyboard::Down))
    {
        m_selectFlag = false;
    }
    
    // �t���O���ƂɃZ���N�g�A�C�R���̈ʒu���ړ�
    if (m_selectFlag)
    {
        m_selectArrowPos = SELECTARROW_POS_1;
    }
    else
    {
        m_selectArrowPos = SELECTARROW_POS_2;
    }

    // �V�[���J��
    if (kb->IsKeyPressed(DirectX::Keyboard::Space) && m_selectFlag)
    {
        m_titleScene->ChangeScene();
    }
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();
    // �w�i
    m_spriteBatch->Draw(m_backGround_Tex.Get(), BACKGROUND_POS);
    // �Q�[���^�C�g��
    m_spriteBatch->Draw(m_gameTitle_Tex.Get(), GAMETITLE_POS);
    // �I�𕶎�
    m_spriteBatch->Draw(m_select_Tex.Get(),SELECT_POS);
    // �I����
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_selectArrowPos);
    // i�̕���
    m_spriteBatch->Draw(m_i_Tex.Get(), I_POS, nullptr, 
        Colors::White, XMConvertToRadians(m_rotate),I_CENTER_POS);
    // o�̕���
    m_spriteBatch->Draw(m_o_Tex.Get(),O_POS, nullptr, 
        Colors::White, XMConvertToRadians(m_rotate), O_CENTER_POS);

    m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}