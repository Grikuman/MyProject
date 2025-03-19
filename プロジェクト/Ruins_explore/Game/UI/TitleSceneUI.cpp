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
    m_titleText_Tex{},
    m_playText_Tex{},
    m_endText_Tex{},
    m_SpaceConfilmText_Tex{},
    m_selectArrow_Tex{},
    m_backGround_Tex{},
    m_selectFlag{true},
    m_titleScene{titlescene},
    m_alpha{},
    m_color{},
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
    m_titleText_Tex = Resources::GetInstance()->GetTexture(L"TitleText");
    m_playText_Tex = Resources::GetInstance()->GetTexture(L"PlayText");
    m_endText_Tex = Resources::GetInstance()->GetTexture(L"EndText");
    m_SpaceConfilmText_Tex = Resources::GetInstance()->GetTexture(L"SpaceConfilmText");
    m_selectArrow_Tex = Resources::GetInstance()->GetTexture(L"SelectArrow");
    m_backGround_Tex = Resources::GetInstance()->GetTexture(L"TitleBackGround");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // �����̓_��
    m_alpha += 0.1f;
    // �_�ł͈̔�(0.0f����1.0f�̊�)
    float alpha = 0.7f + (sinf(m_alpha * 1.0f) * 0.3f);
    // �_�ŐF��ݒ�
    m_color = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, alpha);

    // �I���t���O�ł̏���������
    SelectFlagProcess();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n����
    m_spriteBatch->Begin();

    // �w�i�摜�̕\��
    m_spriteBatch->Draw(m_backGround_Tex.Get(), BACKGROUND_POS);
    // �wRuins Explorer�x�����̕\��
    m_spriteBatch->Draw(m_titleText_Tex.Get(), TITLETEXT_POS);
    // �w�v���C����x�����̕\��
    m_spriteBatch->Draw(m_playText_Tex.Get(),PLAYTEXT_POS);
    // �w�I������x�����̕\��
    m_spriteBatch->Draw(m_endText_Tex.Get(), ENDTEXT_POS);
    // �w�X�y�[�X�L�[�Ō��肷��x�����̕\��
    m_spriteBatch->Draw(m_SpaceConfilmText_Tex.Get(), SPACECONFILMTEXT_POS,nullptr,m_color);
    // �I����̕\��
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_selectArrowPos);

    // �ʏ�̃X�v���C�g�o�b�`���I������
    m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}

//---------------------------------------------------------
// �I���t���O�ł̏���������
//---------------------------------------------------------
void TitleSceneUI::SelectFlagProcess()
{
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

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
    if (kb->IsKeyPressed(DirectX::Keyboard::Space))
    {
        if (m_selectFlag)
        {
            // �v���C����
            m_titleScene->ChangeScene();
        }
        else
        {
            // �I������
            PostQuitMessage(0); // 
        }
    }
}
