#pragma once

#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

class TextUI
{
public:
    TextUI(ID3D11Device* device, ID3D11DeviceContext* context);
    ~TextUI();

    void Update(float elapedTime);
    void Render();
    void Finalize();

private:
    const float width = 1280;
    const float height = 720;

    std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
    std::unique_ptr<DirectX::SpriteFont> spriteFont;

    //Œo‰ßŽžŠÔ
    float m_time;
};
