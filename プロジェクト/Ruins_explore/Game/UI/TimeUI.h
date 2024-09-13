#pragma once

#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

class TimeUI
{
public:
    TimeUI(ID3D11Device* device, ID3D11DeviceContext* context);
    ~TimeUI();

    void Update(float elapedTime);
    void Render();
    void Finalize();

private:
    const float width = 1280;
    const float height = 720;

    DirectX::SpriteBatch* m_spriteBatch;
    DirectX::SpriteFont* m_spriteFont;

    //Œo‰ßŽžŠÔ
    float m_time;
};
