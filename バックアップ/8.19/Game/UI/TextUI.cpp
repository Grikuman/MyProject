#include "pch.h"
#include "TextUI.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
TextUI::TextUI(ID3D11Device* device, ID3D11DeviceContext* context)
    :
    m_time{}
{
    // スプライトバッチとスプライトフォントを初期化
    spriteBatch = std::make_unique<SpriteBatch>(context);
    spriteFont = std::make_unique<SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");
}

/// <summary>
/// Destructor
/// </summary>
TextUI::~TextUI()
{
    Finalize();
}

void TextUI::Update(float elapedTime)
{
    m_time = elapedTime;
}

/// <summary>
/// Render 
/// </summary>
void TextUI::Render()
{
    spriteBatch->Begin();

    // 数値を文字列に変換
    std::wstring timeString = L"TimeLimit : " + std::to_wstring(m_time);

    // 表示するテキスト、位置、色を指定して描画
    spriteFont->DrawString(spriteBatch.get(), timeString.c_str(), 
        SimpleMath::Vector2(width - 400, 20), // position
        Colors::White,                        // color
        0.f,                                  // rotate
        SimpleMath::Vector2::Zero,
        1.4f                                  // scale
    );

    spriteBatch->End();
}

/// <summary>
/// Finalize 
/// </summary>
void TextUI::Finalize()
{
    spriteBatch.reset();
    spriteFont.reset();
}
