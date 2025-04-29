/*
    ファイル名：TimeUI.cpp
    　　　概要：時間のUIを管理するクラス
*/
#include "pch.h"
#include "TimeUI.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TimeUI::TimeUI()
    :
    m_time{},
    m_renderVal{},
    m_timeText{}
{
    // スプライトバッチとスプライトフォントを初期化
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    m_spriteFont = Graphics::GetInstance()->GetFont();
    // 数値描画用クラスを作成する
    m_number = std::make_unique<RenderNumber>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TimeUI::~TimeUI()
{
    Finalize();
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TimeUI::Initialize()
{
    // 画像を取得する
    m_timeText = Resources::GetInstance()->GetTexture(L"TimeText");
    // 数値描画用クラスを初期化する
    m_number->Initialize(Graphics::GetInstance()->GetDeviceResources());
    // UVサイズを設定
    m_number->SetUVSize(UV_SIZE);
    // 画面上の描画位置を設定
    m_number->SetPosition(RENDER_POS);
    // 描画する桁数（1桁のみ表示）
    m_number->SetRenderColumn(1);
    // 桁数を超える数字が表示されるかどうかを設定する
    m_number->SetRenderOverColumn(true);
    // 数字の描画方向を設定（左寄せ）
    m_number->SetDirection(RenderNumber::RenderDirection::LeftAlignment);
    // 数字の色を設定（メインカラーとアウトライン風カラー）
    m_number->SetNumberColor(MAIN_COLOR, OUTLINE_COLOR);
    // 背景色を設定（透明）
    m_number->SetBackColor(BACK_COLOR);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TimeUI::Update(float elapsedTime)
{
    // 時間を加算する
    m_time++;
    // 数字表示を更新する
    m_number->Update(elapsedTime);
    // 表示する数値を加算する
    if (m_time >= COUNT_INTERVAL)
    {
        m_renderVal++;
        m_time = 0.0f;
    }
    // 表示用の数値を設定する
    m_number->SetRenderValue(m_renderVal, false);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TimeUI::Render()
{
    // カウントを表示する
    m_number->Render();
    // テキストの開始
    m_spriteBatch->Begin();
    // テキスト表示
    m_spriteBatch->Draw(m_timeText.Get(),TEXT_POS);
    // スプライトバッチの終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void TimeUI::Finalize()
{
    
}
