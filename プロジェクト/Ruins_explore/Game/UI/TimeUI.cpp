#include "pch.h"
#include "TimeUI.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// </summary>
TimeUI::TimeUI(ID3D11Device* device, ID3D11DeviceContext* context)
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
TimeUI::~TimeUI()
{
    Finalize();
}

void TimeUI::Update(float elapedTime)
{
    m_time = elapedTime;
}

/// <summary>
/// Render 
/// </summary>
void TimeUI::Render()
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
void TimeUI::Finalize()
{
    spriteBatch.reset();
    spriteFont.reset();
}
