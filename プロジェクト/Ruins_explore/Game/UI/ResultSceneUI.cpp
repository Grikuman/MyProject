/*
    ファイル名：ResultSceneUI.cpp
    　　　概要：リザルトシーンのUIを管理するクラス
*/
#include "pch.h"
#include "ResultSceneUI.h"
#include "Game/Scene/ResultScene.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultSceneUI::ResultSceneUI(ResultScene* result)
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
    // スプライトバッチを取得する
    m_spriteBatch     = Graphics::GetInstance()->GetSpriteBatch();
    // 画像を取得する
    m_backGround_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/リザルト背景.png");
    m_tutorialIcon_Tex = Resources::GetInstance()->GetTexture(L"TutorialIcon");
    m_stage1Icon_Tex = Resources::GetInstance()->GetTexture(L"Stage1Icon");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultSceneUI::Update()
{
   
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultSceneUI::Render()
{
    using namespace DirectX::SimpleMath;

    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // 背景を表示する
    m_spriteBatch->Draw(m_backGround_Tex.Get(), BACKGROUND_POS);
    
    // 通常のスプライトバッチを終了
    m_spriteBatch->End();

    // 各ステージごとの描画を分ける
    int stageNumber = Data::GetInstance()->GetMapSelectStage();
    switch (stageNumber)
    {
    case 0:
        TutorialRender();
        break;
    case 1:
        Stage1Render();
        break;
    default:
        break;
    }
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultSceneUI::Finalize()
{
   
}

//---------------------------------------------------------
// チュートリアルステージの描画
//---------------------------------------------------------
void ResultSceneUI::TutorialRender()
{
    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // チュートリアルのアイコンを表示する
    m_spriteBatch->Draw(m_tutorialIcon_Tex.Get(), ICON_POS[0]);

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ステージ1の描画
//---------------------------------------------------------
void ResultSceneUI::Stage1Render()
{
    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ステージ1のアイコンを表示する
    m_spriteBatch->Draw(m_stage1Icon_Tex.Get(), ICON_POS[1]);

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}
