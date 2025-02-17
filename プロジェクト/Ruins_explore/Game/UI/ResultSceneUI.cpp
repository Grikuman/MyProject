/*
    �t�@�C�����FResultSceneUI.cpp
    �@�@�@�T�v�F���U���g�V�[����UI���Ǘ�����N���X
*/
#include "pch.h"
#include "ResultSceneUI.h"
#include "Game/Scene/ResultScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ResultSceneUI::ResultSceneUI(ResultScene* result)
    :
    m_clearText_Tex{},
    m_deadText_Tex{},
    m_clear_Tex{},
    m_dead_Tex{},
    m_spaceKeyText_Tex{},
    m_spaceAlpha{1.0f},
    m_time{}
{
    
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
ResultSceneUI::~ResultSceneUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ResultSceneUI::Initialize()
{
    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch     = Graphics::GetInstance()->GetSpriteBatch();
    // �摜���擾����
    m_clearText_Tex    = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Clear_Text.png");
    m_deadText_Tex     = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Dead_Text.png");;
    m_clear_Tex        = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Clear.png");;
    m_dead_Tex         = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Dead.png");
    m_spaceKeyText_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/PushSpaceKey.png");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ResultSceneUI::Update()
{
    // �_�ł̑��x��ݒ�
    float blinkSpeed = 5.0f; // 1�b�Ԃ�1��_��
    // ���ԉ��Z
    m_time += 0.016f;
    // 0����1�̊Ԃŕω�������
    m_spaceAlpha = (sin(m_time * blinkSpeed) + 1) / 2; 
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ResultSceneUI::Render()
{
    using namespace DirectX::SimpleMath;

    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    // �� ���U���g���ʂŕ\����ύX���� ��
    if (Data::GetInstance()->GetPlaySceneResult()) // ����
    {
        m_spriteBatch->Draw(m_clear_Tex.Get(), CLEAR_POS);
        m_spriteBatch->Draw(m_clearText_Tex.Get(), CLEAR_TEXT_POS);
    }
    else // ���S
    {
        m_spriteBatch->Draw(m_dead_Tex.Get(), DEAD_POS);
        m_spriteBatch->Draw(m_deadText_Tex.Get(), DEAD_TEXT_POS);
    }
    
    // �X�y�[�X�L�[
    m_spriteBatch->Draw(
        m_spaceKeyText_Tex.Get(), SPACEKEY_TEXT_POS, 
        Color(SPACEKEY_TEXT_COLOR_R, SPACEKEY_TEXT_COLOR_G, SPACEKEY_TEXT_COLOR_B, m_spaceAlpha));

    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ResultSceneUI::Finalize()
{
   
}