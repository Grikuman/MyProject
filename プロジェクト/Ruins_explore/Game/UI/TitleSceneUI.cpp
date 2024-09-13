/*
    @file    TitleSceneUI.cpp
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "TitleSceneUI.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "PlayerUIManager.h"
#include "WorkTool/Graphics.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI(Player* player)
    :
    m_player{player},
    m_backGroundPos{}
{
    // �X�e�[�^�X�A�C�R���̈ʒu��ݒ肷��
    m_backGroundPos = Vector2(0.f, 0.f);
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
    // Direct3D���\�[�X�̏�����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // �摜��ǂݍ���
    CreateWICTextureFromFile(device, context, L"Resources/Textures/Status_icon.png", nullptr, m_tex_backGround.GetAddressOf());

    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    // �X�e�[�^�X�A�C�R����`�悷��
    m_spriteBatch->Draw(m_tex_backGround.Get(), m_backGroundPos);

    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}