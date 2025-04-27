/*
    ファイル名：InvincibleEffect.cpp
    　　　概要：プレイヤーの無敵エフェクトを管理するクラス
*/
#pragma once
#include "pch.h"
#include "Game/Effect/InvincibleEffect.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
InvincibleEffect::InvincibleEffect(Player* player)
    :
    m_player{ player },
    m_sphere{},
    m_blendState{ nullptr },
    m_alpha{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
InvincibleEffect::~InvincibleEffect()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void InvincibleEffect::Initialize()
{
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // 球を作成する
    m_sphere = DirectX::GeometricPrimitive::CreateSphere(context, SIZE);

    // ブレンドステートを作成する
    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    device->CreateBlendState(&blendDesc, &m_blendState);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void InvincibleEffect::Update()
{
    // 無敵時間の場合
    if (m_player->GetInvincible())
    {
        m_alpha = ALPHA;   // アルファ値を設定する
    }
    // 無敵時間でない場合
    else
    {
        m_alpha -= ALPHA_DECREASE_SPEED; // アルファ値を減少させる
    }

    // アルファ値の制限
    if (m_alpha <= 0.0f)
    {
        m_alpha = 0.0f;
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void InvincibleEffect::Render()
{
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // ブレンドステートを有効にする
    float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    context->OMSetBlendState(m_blendState, blendFactor, 0xFFFFFFFF);

    // 球体の色と透明度を設定
    DirectX::SimpleMath::Color color(1.0f, 1.0f, 1.0f, m_alpha);

    // 球体のワールド行列を計算する
    DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_player->GetPosition() + SHIFT_POS);
    // 球体を描画する
    m_sphere->Draw(world, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix(), color);

    // ブレンドステートをリセットする
    context->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void InvincibleEffect::Finalize()
{
    // ブレンドステートを解放
    if (m_blendState)
    {
        m_blendState->Release();
        m_blendState = nullptr;
    }
    // 球体もリセット
    m_sphere.reset();
}
