/*
    ファイル名：TimeUI.cpp
    　　　概要：時間のUIを管理するクラス
*/
#include "pch.h"
#include "TimeUI.h"
#include "Framework/Graphics.h"
#include "Framework/InputDevice.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TimeUI::TimeUI(ID3D11Device* device, ID3D11DeviceContext* context)
    :
    m_time{},
    m_renderVal{},
    m_timeText{}
{
    // スプライトバッチとスプライトフォントを初期化
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    m_spriteFont = Graphics::GetInstance()->GetFont();
    m_number = std::make_unique<RenderNumber>();
    m_number->Initialize(Graphics::GetInstance()->GetDeviceResources());
    // UVサイズを設定する
    m_number->SetUVSize(0.05f * 1.0f, 0.125f * 1.0f);

    m_number->SetPosition(950.0f, 600.0f);

    m_number->SetRenderColumn(1);

    m_number->SetRenderOverColumn(true);

    m_number->SetDirection(RenderNumber::RenderDirection::LeftAlignment);

    m_number->SetNumberColor(
    //  メインの色　例：白
    DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
    //  アウトラインモドキの色　例：黒
    DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    m_number->SetBackColor(DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TimeUI::~TimeUI()
{
    Finalize();
}

void TimeUI::Initialize()
{
    m_timeText = Resources::GetInstance()->GetTexture(L"Time_Text");
}

//---------------------------------------------------------
// 更新する
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
// 描画する
//---------------------------------------------------------
void TimeUI::Render()
{
    using namespace DirectX;

    // カウントを表示する
    m_number->Render();

    // テキストの開始
    m_spriteBatch->Begin();

    // テキスト表示
    m_spriteBatch->Draw(m_timeText.Get(), DirectX::SimpleMath::Vector2(880, 0));

    // スプライトバッチの終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void TimeUI::Finalize()
{
    
}
