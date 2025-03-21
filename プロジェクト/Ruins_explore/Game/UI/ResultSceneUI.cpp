/*
    �t�@�C�����FResultSceneUI.cpp
    �@�@�@�T�v�F���U���g�V�[����UI���Ǘ�����N���X
*/
#include "pch.h"
#include "ResultSceneUI.h"
#include "Game/Scene/ResultScene.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ResultSceneUI::ResultSceneUI(ResultScene* result)
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
    // �X�v���C�g�o�b�`���擾����
    m_spriteBatch     = Graphics::GetInstance()->GetSpriteBatch();
    // �摜���擾����
    m_backGround_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/���U���g�w�i.png");
    m_tutorialIcon_Tex = Resources::GetInstance()->GetTexture(L"TutorialIcon");
    m_stage1Icon_Tex = Resources::GetInstance()->GetTexture(L"Stage1Icon");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ResultSceneUI::Update()
{
   
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ResultSceneUI::Render()
{
    using namespace DirectX::SimpleMath;

    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    // �w�i��\������
    m_spriteBatch->Draw(m_backGround_Tex.Get(), BACKGROUND_POS);
    
    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();

    // �e�X�e�[�W���Ƃ̕`��𕪂���
    int stageNumber = Data::GetInstance()->GetMapSelectStage();
    switch (stageNumber)
    {
    case 0:
        TutorialRender();
        break;
    case 1:
        Stage1Render();
        break;
    default:
        break;
    }
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ResultSceneUI::Finalize()
{
   
}

//---------------------------------------------------------
// �`���[�g���A���X�e�[�W�̕`��
//---------------------------------------------------------
void ResultSceneUI::TutorialRender()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    // �`���[�g���A���̃A�C�R����\������
    m_spriteBatch->Draw(m_tutorialIcon_Tex.Get(), ICON_POS[0]);

    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// �X�e�[�W1�̕`��
//---------------------------------------------------------
void ResultSceneUI::Stage1Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    // �X�e�[�W1�̃A�C�R����\������
    m_spriteBatch->Draw(m_stage1Icon_Tex.Get(), ICON_POS[1]);

    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}
