#include "pch.h"
#include "TimeUI.h"
#include "WorkTool/Graphics.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TimeUI::TimeUI(ID3D11Device* device, ID3D11DeviceContext* context)
    :
    m_time{}
{
    // �X�v���C�g�o�b�`�ƃX�v���C�g�t�H���g��������
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    m_spriteFont = Graphics::GetInstance()->GetFont();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TimeUI::~TimeUI()
{
    Finalize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TimeUI::Update(float elapedTime)
{
    m_time = elapedTime;
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TimeUI::Render()
{
    m_spriteBatch->Begin();

    // ���l�𕶎���ɕϊ�
    std::wstring timeString = L"TimeLimit : " + std::to_wstring(m_time);

    // �\������e�L�X�g�A�ʒu�A�F���w�肵�ĕ`��
    m_spriteFont->DrawString(m_spriteBatch, timeString.c_str(), 
        DirectX::SimpleMath::Vector2(width - 400, 20), // position
        DirectX::Colors::White,                        // color
        0.f,                                  // rotate
        DirectX::SimpleMath::Vector2::Zero,
        1.4f                                  // scale
    );

    m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void TimeUI::Finalize()
{
    
}
