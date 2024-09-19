/*
    @file    TitleSceneUI.cpp
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "TitleSceneUI.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI()
    :
    m_ruinsExplorer{},
    m_titleSelect{},
    m_selectIcon{},
    m_selectPos{},
    m_selectFlag{true},
    m_changeSceneFlag{false}
{
    
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
    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    // �摜�ǂݍ���
    m_ruinsExplorer = Resources::GetInstance()->GetTexture(L"Ruins_Explorer");
    m_titleSelect = Resources::GetInstance()->GetTexture(L"TitleSelect");
    m_selectIcon = Resources::GetInstance()->GetTexture(L"SelectIcon");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // �L�[�{�[�h���擾����
    auto kb = Graphics::GetInstance()->GetKeyboardStateTracker();

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
        m_selectPos = Vector2(500, 390);
    }
    else
    {
        m_selectPos = Vector2(500, 510);
    }

    // �V�[���J��
    if (m_selectFlag)
    {
        if (kb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            m_changeSceneFlag = true;
        }
    }
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    // �X�e�[�^�X�A�C�R����`�悷��
    m_spriteBatch->Draw(m_ruinsExplorer.Get(), DirectX::SimpleMath::Vector2(350,150));
    m_spriteBatch->Draw(m_titleSelect.Get(), DirectX::SimpleMath::Vector2(450, 400));
    m_spriteBatch->Draw(m_selectIcon.Get(), m_selectPos);

    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}