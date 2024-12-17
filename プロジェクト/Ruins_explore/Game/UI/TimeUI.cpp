#include "pch.h"
#include "TimeUI.h"
#include "WorkTool/Graphics.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TimeUI::TimeUI(ID3D11Device* device, ID3D11DeviceContext* context)
    :
    m_time{}
{
    // スプライトバッチとスプライトフォントを初期化
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    m_spriteFont = Graphics::GetInstance()->GetFont();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TimeUI::~TimeUI()
{
    Finalize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TimeUI::Update(float elapedTime)
{
    m_time = elapedTime;
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TimeUI::Render()
{
    m_spriteBatch->Begin();

    // 数値を文字列に変換
    std::wstring timeString = L"TimeLimit : " + std::to_wstring(m_time);

    // 表示するテキスト、位置、色を指定して描画
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
// 終了処理
//---------------------------------------------------------
void TimeUI::Finalize()
{
    
}
