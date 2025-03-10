/*
    ファイル名：TimeUI.h
    　　　概要：時間のUIを管理するクラス
*/
#pragma once
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>
#include "RenderNumber.h"

class TimeUI
{
public:
    // コンストラクタ
    TimeUI(ID3D11Device* device, ID3D11DeviceContext* context);
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
    const float width = 1280;
    const float height = 720;

private:
    // 時間
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
