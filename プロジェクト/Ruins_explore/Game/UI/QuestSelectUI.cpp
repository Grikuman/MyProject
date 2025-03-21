/*
    �t�@�C�����FQuestSelectUI.cpp
    �@�@�@�T�v�F�}�b�v�Z���N�g��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "QuestSelectUI.h"
#include "Game/Scene/QuestSelectScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
QuestSelectUI::QuestSelectUI()
    :
    m_SelectMenu_Tex{},
    m_selectArrow_Tex{},
    m_tutorialIcon_Tex{},
    m_stage1Icon_Tex{},
    m_questPopup_Tex{},
    m_selectFlag{},
    m_questArrowPos{},
    m_popupArrowPos{},
    m_popupViewFlag{false},
    m_popupFlag{false},
    m_questStart{false}
{
    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
QuestSelectUI::~QuestSelectUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void QuestSelectUI::Initialize()
{
    // �摜���擾����
    m_SelectMenu_Tex = Resources::GetInstance()->GetTexture(L"SelectMenu");
    m_selectArrow_Tex = Resources::GetInstance()->GetTexture(L"SelectArrow");
    m_tutorialIcon_Tex = Resources::GetInstance()->GetTexture(L"TutorialIcon");
    m_stage1Icon_Tex = Resources::GetInstance()->GetTexture(L"Stage1Icon");
    m_questPopup_Tex = Resources::GetInstance()->GetTexture(L"QuestPopup");
    m_questBoard_Tex[0] = Resources::GetInstance()->GetTexture(L"QuestBoard0");
    m_questBoard_Tex[1] = Resources::GetInstance()->GetTexture(L"QuestBoard1");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void QuestSelectUI::Update()
{
    // �I���t���O�̏���������
    SelectFlagProcess();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void QuestSelectUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n����
    m_spriteBatch->Begin();

    // �I�����j���[��\������
    m_spriteBatch->Draw(m_SelectMenu_Tex.Get(), SELECTMENU_POS);
    // �N�G�X�g�I�����\������
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_questArrowPos);
    // �`���[�g���A���̃A�C�R����\������
    m_spriteBatch->Draw(m_tutorialIcon_Tex.Get(), TUTORIALICON_POS);
    // �X�e�[�W1�̃A�C�R����\������
    m_spriteBatch->Draw(m_stage1Icon_Tex.Get(), STAGE1ICON_POS);
    // �N�G�X�g�{�[�h��\������
    m_spriteBatch->Draw(m_questBoard_Tex[m_selectFlag].Get(), QUEST_BOARD_POS);

    // �ʏ�̃X�v���C�g�o�b�`���I������
    m_spriteBatch->End();

    // �|�b�v�A�b�v�̕`�������
    PopupRender();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void QuestSelectUI::Finalize()
{
   
}

//---------------------------------------------------------
// �I���t���O�̏���������
//---------------------------------------------------------
void QuestSelectUI::SelectFlagProcess()
{
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // * �t���O���Ƃɂ���đI����̈ʒu�����肷�� *
    // �N�G�X�g�I����ʂ̖��̈ʒu
    m_questArrowPos = ARROW_POS[m_selectFlag];
    // �|�b�v�A�b�v��ʂ̖��̈ʒu
    if (m_popupFlag) // �͂�
    {
        m_popupArrowPos = POPUP_ARROW_POS[0];
    }
    else             // ������
    {
        m_popupArrowPos = POPUP_ARROW_POS[1];
    }

    // * �N�G�X�g��I�����鑀�� *
    // �|�b�v�A�b�v���o�Ă��Ȃ���Ԃł̂ݑ���\
    if (!m_popupViewFlag)
    {
        // �N�G�X�g��I�����鑀��
        if (kb->IsKeyPressed((DirectX::Keyboard::Up)))  // ��Ɉړ�
        {
            if (m_selectFlag == 0)
            {
                m_selectFlag = 1;
            }
            else
            {
                m_selectFlag--;
            }
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }
        if (kb->IsKeyPressed((DirectX::Keyboard::Down))) // ���Ɉړ�
        {
            if (m_selectFlag == 1)
            {
                m_selectFlag = 0;
            }
            else
            {
                m_selectFlag++;
            }
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }

        // �N�G�X�g��I�����A�|�b�v�A�b�v������\�ɂ���
        if (kb->IsKeyPressed((DirectX::Keyboard::Space)))
        {
            m_popupViewFlag = true;
            Audio::GetInstance()->PlaySE("QuestSelectSE2");
            return;
        }
    }

    // * �|�b�v�A�b�v���̑��� *
    // �|�b�v�A�b�v���o�Ă����Ԃł̂ݑ���\
    if (m_popupViewFlag)
    {
        // �|�b�v�A�b�v���ł̑I�𑀍�
        if (kb->IsKeyPressed((DirectX::Keyboard::Left)))  // �͂�
        {
            m_popupFlag = true;
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }
        if (kb->IsKeyPressed((DirectX::Keyboard::Right))) // ������
        {
            m_popupFlag = false;
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }

        // �|�b�v�A�b�v���ł̃t���O����
        if (kb->IsKeyPressed((DirectX::Keyboard::Space)))
        {
            // �͂��@��I��ł���ꍇ�̓X�e�[�W�����肷��
            if (m_popupFlag)
            {
                switch (m_selectFlag)
                {
                case 0:
                    Data::GetInstance()->SetMapSelectStage(0);
                    break;
                case 1:
                    Data::GetInstance()->SetMapSelectStage(1);
                    break;
                default:
                    break;
                }
                // �N�G�X�g���J�n����
                m_questStart = true;
            }
            // �������@��I��ł���ꍇ�̓N�G�X�g�I���ɖ߂�
            else
            {
                // �|�b�v�A�b�v����ăN�G�X�g�I���ɖ߂�
                m_popupViewFlag = false;
                Audio::GetInstance()->PlaySE("QuestSelectSE3");
                return;
            }
        }
    }
}

//---------------------------------------------------------
// �|�b�v�A�b�v���ł̕`�������
//---------------------------------------------------------
void QuestSelectUI::PopupRender()
{
    // �|�b�v�A�b�v�̕\���t���O��true�Ȃ�΃|�b�v�A�b�v��\������
    if (m_popupViewFlag)
    {
        // �ʏ�̃X�v���C�g�o�b�`���J�n����
        m_spriteBatch->Begin();

        // �|�b�v�A�b�v��\������
        m_spriteBatch->Draw(m_questPopup_Tex.Get(), POPUP_POS);
        // �|�b�v�A�b�v���ł̖���\������
        m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_popupArrowPos);

        // �ʏ�̃X�v���C�g�o�b�`���I������
        m_spriteBatch->End();
    }
}
