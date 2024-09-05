#pragma once
#include "pch.h"
#include "Game/Effect/SwordEffect.h"
#include <WICTextureLoader.h>
#include "Mouse.h"

SwordEffect::SwordEffect(ID3D11Device* device)
{
    // エフェクトの作成
    m_batchEffect = std::make_unique<DirectX::AlphaTestEffect>(device);
    m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
    m_batchEffect->SetReferenceAlpha(255);

    // 入力レイアウトを生成する
    void const* shaderByteCode;
    size_t byteCodeLength;
    m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    device->CreateInputLayout(
        DirectX::VertexPositionTexture::InputElements,
        DirectX::VertexPositionTexture::InputElementCount,
        shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()
    );

    // 共通ステートを作成する
    m_commonStates = std::make_unique<DirectX::CommonStates>(device);

    // テクスチャをロードする
    for (int i = 0; i < 6; i++)
    {
        DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_1.png", nullptr, m_texture[0].GetAddressOf());
        DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_2.png", nullptr, m_texture[1].GetAddressOf());
        DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_3.png", nullptr, m_texture[2].GetAddressOf());
        DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_4.png", nullptr, m_texture[3].GetAddressOf());
        DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_5.png", nullptr, m_texture[4].GetAddressOf());
        DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_6.png", nullptr, m_texture[5].GetAddressOf());
    }

    m_position = DirectX::SimpleMath::Vector3::Zero; // デフォルト位置

    m_cnt = 0;
}

SwordEffect::~SwordEffect()
{

}

void SwordEffect::Update()
{
    m_cnt++;
    if (m_cnt >= 30)
    {
        m_cnt = 0;
    }
}

void SwordEffect::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
    m_position = position;
}

void SwordEffect::Render(
    ID3D11DeviceContext1* context,
    DirectX::SimpleMath::Matrix view,
    DirectX::SimpleMath::Matrix proj)
{
    // プリミティブバッチの作成
    m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);

    // 頂点情報（板ポリゴンの頂点）
    DirectX::VertexPositionTexture vertex[4] =
    {
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(2.0f, 0.5f, 2.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(-2.0f, 0.5f, 2.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(-2.0f, 0.5f, -2.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(2.0f, 0.5f, -2.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
    };

    // テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード）
    ID3D11SamplerState* samplers[1] = { m_commonStates->PointWrap() };
    context->PSSetSamplers(0, 1, samplers);

    // 深度バッファに書き込み参照する
    context->OMSetDepthStencilState(m_commonStates->DepthDefault(), 0);

    // カリングは左周り（反時計回り）
    context->RSSetState(m_commonStates->CullCounterClockwise());

    // 不透明のみ描画する設定
    m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
    m_batchEffect->SetReferenceAlpha(0);
    m_batchEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
    m_batchEffect->SetView(view);
    m_batchEffect->SetProjection(proj);
    m_batchEffect->SetTexture(m_texture[(m_cnt / 5) % 6].Get());
    m_batchEffect->Apply(context);
    context->IASetInputLayout(m_inputLayout.Get());

    // 半透明部分を描画
    m_primitiveBatch->Begin();
    m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
    m_primitiveBatch->End();
}

void SwordEffect::Finalize()
{

}
