#pragma once

#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

class TimeUI
{
public:
    // コンストラクタ
    TimeUI(ID3D11Device* device, ID3D11DeviceContext* context);
    // デストラクタ
    ~TimeUI();
    // 更新する
    void Update(float elapedTime);
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    const float width = 1280;
    const float height = 720;

private:
    // スプラインバッチ
    DirectX::SpriteBatch* m_spriteBatch;
    // スプライトフォント
    DirectX::SpriteFont* m_spriteFont;

    //経過時間
    float m_time;
};
