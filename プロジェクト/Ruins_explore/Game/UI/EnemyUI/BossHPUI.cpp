/*
    ファイル名：BossHPUI.h
    　　　概要：ボスの体力UIを管理するクラス
*/

#include "pch.h"
#include "BossHPUI.h"
#include "UserInterface.h"
#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include <vector>
#include <string>

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
BossHPUI::BossHPUI()
    : m_menuIndex(0)
    ,m_windowHeight(0)
    ,m_windowWidth(0)
    ,m_pDR(nullptr)
    ,m_baseTexturePath(nullptr)
    ,m_BossHPUI(nullptr)
    ,m_frame(nullptr)
    ,m_spriteBatch{}
    ,m_spriteFont{}
    ,m_currentHP{}
    ,m_maxHP{}
{
    
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
BossHPUI::~BossHPUI()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void BossHPUI::Initialize(DX::DeviceResources* pDR,int width,int height)
{
    // デバイス・画面サイズを設定
	m_pDR = pDR;
    m_windowWidth = width;
    m_windowHeight = height;
    // 体力ゲージ(緑)のパスを指定する
    m_baseTexturePath = L"Resources/Textures/HP.jpg";
    // テクスチャ
    Add(L"Resources/Textures/HP_red.jpg"
        , DirectX::SimpleMath::Vector2(width / 2, 50.0f)
        , DirectX::SimpleMath::Vector2(1.0f,1.0f)
        , UserInterface::MIDDLE_CENTER);
    // スプライトバッチ
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    // スプライトフォント
    m_spriteFont = Graphics::GetInstance()->GetFont();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void BossHPUI::Update(float bossHP,float MAX_BossHP)
{
    m_currentHP = bossHP;
    m_maxHP = MAX_BossHP;
    // 比率
    float ratio;
    // 現在の体力割合を計算する
    ratio = m_currentHP / m_maxHP;
    // 比率を設定する
    m_BossHPUI->SetRenderRatio(ratio);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void BossHPUI::Render()
{
    // 各テクスチャを描画する
    m_base->Render();
    m_BossHPUI->Render();
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

//---------------------------------------------------------
// 追加する
//---------------------------------------------------------
void BossHPUI::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
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
    m_BossHPUI = std::make_unique<UserInterface>();
    m_BossHPUI->Create(m_pDR
        , m_baseTexturePath
        , position
        , scale
        , anchor);
    m_BossHPUI->SetWindowSize(m_windowWidth, m_windowHeight);
    m_BossHPUI->SetRenderRatioOffset(0.f);
    //m_BossHPUI->SetRenderRatioOffset(0.3f);

    // 体力ゲージの枠を作成する
    m_frame = std::make_unique<UserInterface>();
    m_frame->Create(m_pDR
        , path
        , position + DirectX::SimpleMath::Vector2(0.f, 5.f)
        , scale
        , anchor);
    m_frame->SetWindowSize(m_windowWidth, m_windowHeight);
}


