/*
    ファイル名：TimeUI.h
    　　　概要：時間のUIを管理するクラス
*/
#pragma once
#include "RenderNumber.h"

class TimeUI
{
public:
    // コンストラクタ
    TimeUI();
    // デストラクタ
    ~TimeUI();
    // 初期化する
    void Initialize();
    // 更新する
    void Update(float elapsedTime);
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    // テキストの表示位置
    const DirectX::SimpleMath::Vector2 TEXT_POS = { 880.0f,0.0f };
    // UVサイズ
    const DirectX::SimpleMath::Vector2 UV_SIZE = { 0.05f,0.125f };
    // 数字の描画位置
    const DirectX::SimpleMath::Vector2 RENDER_POS = { 950.0f,600.0f };
    // 数字のメインカラー
    const DirectX::SimpleMath::Vector4 MAIN_COLOR = { 1.0f,1.0f,1.0f,1.0f };
    // 数字のアウトラインカラー
    const DirectX::SimpleMath::Vector4 OUTLINE_COLOR = { 0.0f,0.0f,0.0f,0.0f };
    // 背景色
    const DirectX::SimpleMath::Vector4 BACK_COLOR = { 0.0f,0.0f,0.0f,0.0f };
    // カウントの間隔(1カウントに必要なフレーム)
    const float COUNT_INTERVAL = 60.0f;

private:
    // 数値描画用クラス
    std::unique_ptr<RenderNumber> m_number;
    // 描画する数値
    uint64_t m_renderVal;
    //経過時間
    float m_time;
    // スプラインバッチ
    DirectX::SpriteBatch* m_spriteBatch;
    // スプライトフォント
    DirectX::SpriteFont* m_spriteFont;
    // テキスト(残り時間)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeText;
};
