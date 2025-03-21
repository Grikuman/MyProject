/*
    �t�@�C�����FTutorialGuideUI.cpp
    �@�@�@�T�v�F�}�b�v�Z���N�g��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "TutorialGuideUI.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Data.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TutorialGuideUI::TutorialGuideUI()
    :
    m_guideMissionText_Tex{},
    m_missionCheckMark_Tex{},
    m_missionFlag{},
    m_missionClearCnt{}
{
    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TutorialGuideUI::~TutorialGuideUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TutorialGuideUI::Initialize()
{
    // �摜���擾����
    m_guideMissionText_Tex = Resources::GetInstance()->GetTexture(L"TutorialGuideMissionText");
    m_missionCheckMark_Tex = Resources::GetInstance()->GetTexture(L"MissionCheckMark");

    // �~�b�V�����t���O�̏�����
    for (int i = 0; i < 4; i++)
    {
        m_missionFlag[i] = false;
    }
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TutorialGuideUI::Update()
{
    m_missionClearCnt = 0;
    // �~�b�V�������N���A�����ꍇ�A4�Ԗڂ̃~�b�V�������N���A����
    for (int i = 0; i < 3; i++)
    {
        if (m_missionFlag[i])
        {
            m_missionClearCnt++;
        }
    }
    // �S�Ẵ~�b�V�������N���A���Ă����ꍇ
    if (m_missionClearCnt == 3)
    {
        m_missionFlag[3] = true;
    }
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TutorialGuideUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n����
    m_spriteBatch->Begin();

    // �I�����j���[��\������
    m_spriteBatch->Draw(m_guideMissionText_Tex.Get(), GUIDEMISSION_POS);

    for (int i = 0; i < 4; i++)
    {
        if (m_missionFlag[i])
        {
            m_spriteBatch->Draw(m_missionCheckMark_Tex.Get(), MISSIONCHECKMARK_POS[i]);
        }
    }

    // �ʏ�̃X�v���C�g�o�b�`���I������
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TutorialGuideUI::Finalize()
{
   
}