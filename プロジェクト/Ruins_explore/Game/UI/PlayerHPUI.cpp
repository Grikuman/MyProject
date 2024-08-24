/*
    @file    PlayerHPUI.cpp
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerHPUI.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "PlayerUIManager.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerHPUI::PlayerHPUI(Player* player)
    :
    m_player{player},
    m_commonResources{},
    MAXHP{m_player->GetMAXHP()},
    m_position{},
    m_backPosition{},
    m_scale{1.f},
    m_matrix{},
    m_tex_Green{},
    m_tex_Red{},
    m_tex_BackGround{}
{
    m_hp = MAXHP; //�̗͂�ݒ肷��
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerHPUI::~PlayerHPUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerHPUI::Initialize(CommonResources* resources)
{
    assert(resources);
    m_commonResources = resources;

    // UI�ʒu��ݒ肷��
    m_position = Vector2(60, 40);
    // �w�i�̈ʒu��ݒ肷��
    m_backPosition = Vector2(10,10);

    // Direct3D���\�[�X�̏�����
    auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

    // �摜��ǂݍ���
    CreateWICTextureFromFile(device, context, L"Resources/Textures/HP.jpg", nullptr, m_tex_Green.GetAddressOf());
    CreateWICTextureFromFile(device, context, L"Resources/Textures/HP_red.jpg", nullptr, m_tex_Red.GetAddressOf());
    CreateWICTextureFromFile(device, context, L"Resources/Textures/HP_Back.png", nullptr, m_tex_BackGround.GetAddressOf());

    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerHPUI::Update()
{
    // HP���擾����
    m_hp = m_player->GetHP();
    // ���݂�HP�������v�Z
    m_scale = m_hp / MAXHP;
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerHPUI::Render()
{
    // HP�̕\���͈͂�ݒ肷��(scale���\������)
    //HP�o�[�̈ʒu�����_�Ɉړ�����
    Matrix translation = Matrix::CreateTranslation(-m_position.x, -m_position.y, 0.0f);
    // �X�P�[����ݒ�
    Matrix scaling = Matrix::CreateScale(m_scale, 1.f, 1.f);
    // �X�P�[�����O��Ɍ��̈ʒu�ɖ߂�
    Matrix reverseTranslation = Matrix::CreateTranslation(m_position.x, m_position.y, 0.0f);
    Matrix matrix = translation * scaling * reverseTranslation;

    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();
    // �w�i��`�悷��
    m_spriteBatch->Draw(m_tex_BackGround.Get(), m_backPosition);
    // �̗�(��)
    m_spriteBatch->Draw(m_tex_Red.Get(), m_position);
    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();

    // �̗͌����p�X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, nullptr, matrix);
    // �̗͂�`�悷��
    m_spriteBatch->Draw(m_tex_Green.Get(), m_position);
    // �̗͌����p�X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerHPUI::Finalize()
{
   
}