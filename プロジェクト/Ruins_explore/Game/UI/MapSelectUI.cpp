/*
    �t�@�C�����FMapSelectUI.cpp
    �@�@�@�T�v�F�}�b�v�Z���N�g��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "MapSelectUI.h"
#include "Game/Scene/MapSelectScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Data.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MapSelectUI::MapSelectUI(MapSelectScene* mapSelectScene)
    :
    m_mapSelectScene{mapSelectScene},
    m_SelectMenu_Tex{},
    m_selectArrow_Tex{},
    m_tutorialIcon_Tex{},
    m_stage1Icon_Tex{},
    m_selectFlag{},
    m_selectArrowPos{}
{
    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MapSelectUI::~MapSelectUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MapSelectUI::Initialize()
{
    m_SelectMenu_Tex = Resources::GetInstance()->GetTexture(L"SelectMenu");
    m_selectArrow_Tex = Resources::GetInstance()->GetTexture(L"SelectArrow");
    m_tutorialIcon_Tex = Resources::GetInstance()->GetTexture(L"TutorialIcon");
    m_stage1Icon_Tex = Resources::GetInstance()->GetTexture(L"Stage1Icon");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MapSelectUI::Update()
{
    // �I���t���O�̏���������
    SelectFlagProcess();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MapSelectUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n����
    m_spriteBatch->Begin();

    // �I�����j���[��\������
    m_spriteBatch->Draw(m_SelectMenu_Tex.Get(), SELECTMENU_POS);
    // �I�����\������
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_selectArrowPos);
    // �`���[�g���A���̃A�C�R����\������
    m_spriteBatch->Draw(m_tutorialIcon_Tex.Get(), TUTORIALICON_POS);
    // �X�e�[�W1�̃A�C�R����\������
    m_spriteBatch->Draw(m_stage1Icon_Tex.Get(), STAGE1ICON_POS);

    // �ʏ�̃X�v���C�g�o�b�`���I������
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MapSelectUI::Finalize()
{
   
}

//---------------------------------------------------------
// �I���t���O�̏���������
//---------------------------------------------------------
void MapSelectUI::SelectFlagProcess()
{
    // �L�[�{�[�h���擾����
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    if (kb->IsKeyPressed((DirectX::Keyboard::Up)))
    {
        if (m_selectFlag == 0)
        {
            m_selectFlag = 1;
        }
        else
        {
            m_selectFlag--;
        }
    }
    if (kb->IsKeyPressed((DirectX::Keyboard::Down)))
    {
        if (m_selectFlag == 1)
        {
            m_selectFlag = 0;
        }
        else
        {
            m_selectFlag++;
        }
    }
    switch (m_selectFlag)
    {
    case 0:
        m_selectArrowPos = SELECTARROW_POS_0;
        break;
    case 1:
        m_selectArrowPos = SELECTARROW_POS_1;
        break;
    default:
        break;
    }

    // �I���t���O���Ƃ̃V�[���J�ڂ̏���
    if (kb->IsKeyPressed((DirectX::Keyboard::Space)))
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
        // �v���C�V�[���Ɉڍs
        m_mapSelectScene->ChangeScene();
    }
}
