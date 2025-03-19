/*
    �t�@�C�����FTimeUI.cpp
    �@�@�@�T�v�F���Ԃ�UI���Ǘ�����N���X
*/
#include "pch.h"
#include "TimeUI.h"
#include "Framework/Graphics.h"
#include "Framework/InputDevice.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TimeUI::TimeUI(ID3D11Device* device, ID3D11DeviceContext* context)
    :
    m_time{},
    m_renderVal{},
    m_timeText{}
{
    // �X�v���C�g�o�b�`�ƃX�v���C�g�t�H���g��������
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();  // �X�v���C�g�`��p�o�b�`���擾
    m_spriteFont = Graphics::GetInstance()->GetFont();          // �t�H���g�`��p�I�u�W�F�N�g���擾

    // ���l�`��p��RenderNumber�I�u�W�F�N�g���쐬
    m_number = std::make_unique<RenderNumber>();
    m_number->Initialize(Graphics::GetInstance()->GetDeviceResources()); // ����������

    // UV�T�C�Y��ݒ�i�e�N�X�`���̈ꕔ�����g�p����ꍇ�̃T�C�Y�w��j
    m_number->SetUVSize(0.05f * 1.0f, 0.125f * 1.0f); // ��0.05�A����0.125�ɐݒ�

    // ��ʏ�̕`��ʒu��ݒ�i�X�N���[�����W�j
    m_number->SetPosition(950.0f, 600.0f); // X:950, Y:600 �ɔz�u

    // �`�悷�錅���i1���̂ݕ\���j
    m_number->SetRenderColumn(1);

    // �����𒴂��鐔�����\������邩�ǂ�����ݒ�itrue�ŋ��j
    m_number->SetRenderOverColumn(true);

    // �����̕`�������ݒ�i���񂹁j
    m_number->SetDirection(RenderNumber::RenderDirection::LeftAlignment);

    // �����̐F��ݒ�i���C���J���[�ƃA�E�g���C�����J���[�j
    m_number->SetNumberColor(
        DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f), // ���C���̐F�i���j
        DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f)  // �A�E�g���C�����̐F�i���j
    );

    // �w�i�F��ݒ�i�����j
    m_number->SetBackColor(DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f)); // �����i��+�A���t�@0�j
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TimeUI::~TimeUI()
{
    Finalize();
}

void TimeUI::Initialize()
{
    m_timeText = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Time_Text.png");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TimeUI::Update(float elapsedTime)
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    m_time++;

    m_number->Update(elapsedTime);

    if (m_time >= 60)
    {
        m_renderVal++;
        m_time = 0;
    }

    m_number->SetRenderValue(m_renderVal, false);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TimeUI::Render()
{
    using namespace DirectX;

    // �J�E���g��\������
    m_number->Render();

    // �e�L�X�g�̊J�n
    m_spriteBatch->Begin();

    // �e�L�X�g�\��
    m_spriteBatch->Draw(m_timeText.Get(), DirectX::SimpleMath::Vector2(880, 0));

    // �X�v���C�g�o�b�`�̏I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void TimeUI::Finalize()
{
    
}
