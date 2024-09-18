//--------------------------------------------------------------------------------------
// File: Gauge.cpp
//
// ゲージ
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Gauge.h"
#include "UserInterface.h"

#include "BinaryFile.h"
#include "WorkTool/DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

#include <string>
#include "WorkTool/Graphics.h"

using namespace DirectX;

Gauge::Gauge()
    : m_menuIndex(0)
    ,m_windowHeight(0)
    ,m_windowWidth(0)
    ,m_pDR(nullptr)
    ,m_baseTexturePath(nullptr)
    ,m_gauge(nullptr)
    ,m_frame(nullptr)
    ,m_spriteBatch{}
    ,m_spriteFont{}
    ,m_currentHP{}
    ,m_maxHP{}
{
    
}

Gauge::~Gauge()
{
}

void Gauge::Initialize(DX::DeviceResources* pDR,int width,int height)
{
    // デバイス・画面サイズを設定
	m_pDR = pDR;
    m_windowWidth = width;
    m_windowHeight = height;

    // 体力ゲージ(緑)のパスを指定する
    m_baseTexturePath = L"Resources/Textures/HP.jpg";

    // テクスチャ
    Add(L"Resources/Textures/HealthGaugeFrame.png"
        , SimpleMath::Vector2(width / 2, 50)
        , SimpleMath::Vector2(1.0f,1.0f)
        , UserInterface::MIDDLE_CENTER);

    // スプライトバッチ
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    // スプライトフォント
    m_spriteFont = Graphics::GetInstance()->GetFont();
}

void Gauge::Update(float bossHP,float MAX_BossHP)
{
    m_currentHP = bossHP;
    m_maxHP = MAX_BossHP;
    // 比率
    float ratio;
    // 現在の体力割合を計算する
    ratio = m_currentHP / m_maxHP;
    // 比率を設定する
    m_gauge->SetRenderRatio(ratio);

}

void Gauge::Render()
{
    // 各テクスチャを描画する
    m_base->Render();
    m_gauge->Render();
    //m_frame->Render();

    // スプライトバッチを開始
    m_spriteBatch->Begin();

    // ボス名
    m_spriteFont->DrawString(m_spriteBatch, L"BOSS", DirectX::SimpleMath::Vector2(610,2));
   
    // ボスの体力割合を表示する
    m_spriteFont->DrawString(
        m_spriteBatch,
        (std::to_wstring(static_cast<int>(m_currentHP)) + L"/" + std::to_wstring(static_cast<int>(m_maxHP))).c_str(),
        DirectX::SimpleMath::Vector2(597, 32)
    );
    // スプライトバッチを終了
    m_spriteBatch->End();

}

void Gauge::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
{
    // 体力ゲージ(赤色)を作成する
    m_base = std::make_unique<UserInterface>();
    m_base->Create(m_pDR
        , L"Resources/Textures/HP_red.jpg"
        , position
        , scale
        , anchor);
    m_base->SetWindowSize(m_windowWidth, m_windowHeight);

    // 体力ゲージ(緑色)を作成する
    m_gauge = std::make_unique<UserInterface>();
    m_gauge->Create(m_pDR
        , m_baseTexturePath
        , position
        , scale
        , anchor);
    m_gauge->SetWindowSize(m_windowWidth, m_windowHeight);
    m_gauge->SetRenderRatioOffset(0.f);
    //m_gauge->SetRenderRatioOffset(0.3f);

    // 体力ゲージの枠を作成する
    m_frame = std::make_unique<UserInterface>();
    m_frame->Create(m_pDR
        , path
        , position + DirectX::SimpleMath::Vector2(0.f, 5.f)
        , scale
        , anchor);
    m_frame->SetWindowSize(m_windowWidth, m_windowHeight);
}


