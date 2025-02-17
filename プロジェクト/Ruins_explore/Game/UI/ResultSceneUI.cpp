/*
    ファイル名：ResultSceneUI.cpp
    　　　概要：リザルトシーンのUIを管理するクラス
*/
#include "pch.h"
#include "ResultSceneUI.h"
#include "Game/Scene/ResultScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultSceneUI::ResultSceneUI(ResultScene* result)
    :
    m_clearText_Tex{},
    m_deadText_Tex{},
    m_clear_Tex{},
    m_dead_Tex{},
    m_spaceKeyText_Tex{},
    m_spaceAlpha{1.0f},
    m_time{}
{
    
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ResultSceneUI::~ResultSceneUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ResultSceneUI::Initialize()
{
    // スプライトバッチを設定する
    m_spriteBatch     = Graphics::GetInstance()->GetSpriteBatch();
    // 画像を取得する
    m_clearText_Tex    = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Clear_Text.png");
    m_deadText_Tex     = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Dead_Text.png");;
    m_clear_Tex        = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Clear.png");;
    m_dead_Tex         = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Dead.png");
    m_spaceKeyText_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/PushSpaceKey.png");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultSceneUI::Update()
{
    // 点滅の速度を設定
    float blinkSpeed = 5.0f; // 1秒間に1回点滅
    // 時間加算
    m_time += 0.016f;
    // 0から1の間で変化させる
    m_spaceAlpha = (sin(m_time * blinkSpeed) + 1) / 2; 
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultSceneUI::Render()
{
    using namespace DirectX::SimpleMath;

    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ＜ リザルト結果で表示を変更する ＞
    if (Data::GetInstance()->GetPlaySceneResult()) // 生存
    {
        m_spriteBatch->Draw(m_clear_Tex.Get(), CLEAR_POS);
        m_spriteBatch->Draw(m_clearText_Tex.Get(), CLEAR_TEXT_POS);
    }
    else // 死亡
    {
        m_spriteBatch->Draw(m_dead_Tex.Get(), DEAD_POS);
        m_spriteBatch->Draw(m_deadText_Tex.Get(), DEAD_TEXT_POS);
    }
    
    // スペースキー
    m_spriteBatch->Draw(
        m_spaceKeyText_Tex.Get(), SPACEKEY_TEXT_POS, 
        Color(SPACEKEY_TEXT_COLOR_R, SPACEKEY_TEXT_COLOR_G, SPACEKEY_TEXT_COLOR_B, m_spaceAlpha));

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultSceneUI::Finalize()
{
   
}