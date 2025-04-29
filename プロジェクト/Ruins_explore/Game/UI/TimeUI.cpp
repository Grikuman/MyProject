/*
    �t�@�C�����FTimeUI.cpp
    �@�@�@�T�v�F���Ԃ�UI���Ǘ�����N���X
*/
#include "pch.h"
#include "TimeUI.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TimeUI::TimeUI()
    :
    m_time{},
    m_renderVal{},
    m_timeText{}
{
    // �X�v���C�g�o�b�`�ƃX�v���C�g�t�H���g��������
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    m_spriteFont = Graphics::GetInstance()->GetFont();
    // ���l�`��p�N���X���쐬����
    m_number = std::make_unique<RenderNumber>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TimeUI::~TimeUI()
{
    Finalize();
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TimeUI::Initialize()
{
    // �摜���擾����
    m_timeText = Resources::GetInstance()->GetTexture(L"TimeText");
    // ���l�`��p�N���X������������
    m_number->Initialize(Graphics::GetInstance()->GetDeviceResources());
    // UV�T�C�Y��ݒ�
    m_number->SetUVSize(UV_SIZE);
    // ��ʏ�̕`��ʒu��ݒ�
    m_number->SetPosition(RENDER_POS);
    // �`�悷�錅���i1���̂ݕ\���j
    m_number->SetRenderColumn(1);
    // �����𒴂��鐔�����\������邩�ǂ�����ݒ肷��
    m_number->SetRenderOverColumn(true);
    // �����̕`�������ݒ�i���񂹁j
    m_number->SetDirection(RenderNumber::RenderDirection::LeftAlignment);
    // �����̐F��ݒ�i���C���J���[�ƃA�E�g���C�����J���[�j
    m_number->SetNumberColor(MAIN_COLOR, OUTLINE_COLOR);
    // �w�i�F��ݒ�i�����j
    m_number->SetBackColor(BACK_COLOR);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TimeUI::Update(float elapsedTime)
{
    // ���Ԃ����Z����
    m_time++;
    // �����\�����X�V����
    m_number->Update(elapsedTime);
    // �\�����鐔�l�����Z����
    if (m_time >= COUNT_INTERVAL)
    {
        m_renderVal++;
        m_time = 0.0f;
    }
    // �\���p�̐��l��ݒ肷��
    m_number->SetRenderValue(m_renderVal, false);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TimeUI::Render()
{
    // �J�E���g��\������
    m_number->Render();
    // �e�L�X�g�̊J�n
    m_spriteBatch->Begin();
    // �e�L�X�g�\��
    m_spriteBatch->Draw(m_timeText.Get(),TEXT_POS);
    // �X�v���C�g�o�b�`�̏I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void TimeUI::Finalize()
{
    
}
