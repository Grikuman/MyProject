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
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();  // スプライト描画用バッチを取得
    m_spriteFont = Graphics::GetInstance()->GetFont();          // フォント描画用オブジェクトを取得

    // 数値描画用のRenderNumberオブジェクトを作成
    m_number = std::make_unique<RenderNumber>();
    m_number->Initialize(Graphics::GetInstance()->GetDeviceResources()); // 初期化処理

    // UVサイズを設定（テクスチャの一部分を使用する場合のサイズ指定）
    m_number->SetUVSize(0.05f * 1.0f, 0.125f * 1.0f); // 幅0.05、高さ0.125に設定

    // 画面上の描画位置を設定（スクリーン座標）
    m_number->SetPosition(950.0f, 600.0f); // X:950, Y:600 に配置

    // 描画する桁数（1桁のみ表示）
    m_number->SetRenderColumn(1);

    // 桁数を超える数字が表示されるかどうかを設定（trueで許可）
    m_number->SetRenderOverColumn(true);

    // 数字の描画方向を設定（左寄せ）
    m_number->SetDirection(RenderNumber::RenderDirection::LeftAlignment);

    // 数字の色を設定（メインカラーとアウトライン風カラー）
    m_number->SetNumberColor(
        DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f), // メインの色（白）
        DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f)  // アウトライン風の色（黒）
    );

    // 背景色を設定（透明）
    m_number->SetBackColor(DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f)); // 透明（黒+アルファ0）
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
    m_timeText = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Time_Text.png");
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
