/*
    ファイル名：TitleSceneUI.cpp
    　　　概要：タイトルシーンのUIを管理するクラス
*/
#include "pch.h"
#include "TitleSceneUI.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Game/Scene/TitleScene.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI(TitleScene* titlescene)
    :
    m_spriteBatch{},
    m_titleText_Tex{},
    m_playText_Tex{},
    m_endText_Tex{},
    m_SpaceConfilmText_Tex{},
    m_selectArrow_Tex{},
    m_backGround_Tex{},
    m_selectFlag{true},
    m_titleScene{titlescene},
    m_alpha{},
    m_color{},
    m_selectArrowPos{}
{
    // スプライトバッチを取得する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TitleSceneUI::~TitleSceneUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TitleSceneUI::Initialize()
{
    // 画像読み込み
    m_titleText_Tex = Resources::GetInstance()->GetTexture(L"TitleText");
    m_playText_Tex = Resources::GetInstance()->GetTexture(L"PlayText");
    m_endText_Tex = Resources::GetInstance()->GetTexture(L"EndText");
    m_SpaceConfilmText_Tex = Resources::GetInstance()->GetTexture(L"SpaceConfilmText");
    m_selectArrow_Tex = Resources::GetInstance()->GetTexture(L"SelectArrow");
    m_backGround_Tex = Resources::GetInstance()->GetTexture(L"TitleBackGround");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // 文字の点滅
    m_alpha += 0.1f;
    // 点滅の範囲(0.0fから1.0fの間)
    float alpha = 0.7f + (sinf(m_alpha * 1.0f) * 0.3f);
    // 点滅色を設定
    m_color = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, alpha);

    // 選択フラグでの処理をする
    SelectFlagProcess();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    // 通常のスプライトバッチを開始する
    m_spriteBatch->Begin();

    // 背景画像の表示
    m_spriteBatch->Draw(m_backGround_Tex.Get(), BACKGROUND_POS);
    // 『Ruins Explorer』文字の表示
    m_spriteBatch->Draw(m_titleText_Tex.Get(), TITLETEXT_POS);
    // 『プレイする』文字の表示
    m_spriteBatch->Draw(m_playText_Tex.Get(),PLAYTEXT_POS);
    // 『終了する』文字の表示
    m_spriteBatch->Draw(m_endText_Tex.Get(), ENDTEXT_POS);
    // 『スペースキーで決定する』文字の表示
    m_spriteBatch->Draw(m_SpaceConfilmText_Tex.Get(), SPACECONFILMTEXT_POS,nullptr,m_color);
    // 選択矢印の表示
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_selectArrowPos);

    // 通常のスプライトバッチを終了する
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}

//---------------------------------------------------------
// 選択フラグでの処理をする
//---------------------------------------------------------
void TitleSceneUI::SelectFlagProcess()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // 上キーを押したら
    if (kb->IsKeyPressed(DirectX::Keyboard::Up))
    {
        m_selectFlag = true;
    }
    // 下キーを押したら
    if (kb->IsKeyPressed(DirectX::Keyboard::Down))
    {
        m_selectFlag = false;
    }
    // フラグごとにセレクトアイコンの位置を移動
    if (m_selectFlag)
    {
        m_selectArrowPos = SELECTARROW_POS_1;
    }
    else
    {
        m_selectArrowPos = SELECTARROW_POS_2;
    }

    // シーン遷移
    if (kb->IsKeyPressed(DirectX::Keyboard::Space))
    {
        if (m_selectFlag)
        {
            // プレイする
            m_titleScene->ChangeScene();
        }
        else
        {
            // 終了する
            PostQuitMessage(0); // 
        }
    }
}
