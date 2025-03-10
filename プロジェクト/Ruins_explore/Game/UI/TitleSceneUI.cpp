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
    m_gameTitle_Tex{},
    m_select_Tex{},
    m_selectArrow_Tex{},
    m_i_Tex{},
    m_o_Tex{},
    m_backGround_Tex{},
    m_selectFlag{true},
    m_titleScene{titlescene},
    m_rotate{},
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
    m_gameTitle_Tex   = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Ruins_Explorer.png");
    m_select_Tex      = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/TitleSelect.png");
    m_selectArrow_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/SelectArrow.png");
    m_i_Tex           = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/i.png");
    m_o_Tex           = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/o.png");
    m_backGround_Tex  = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/TitleBackGround.png");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // 文字回転
    m_rotate += 1.f;

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
    if (kb->IsKeyPressed(DirectX::Keyboard::Space) && m_selectFlag)
    {
        m_titleScene->ChangeScene();
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();
    // 背景
    m_spriteBatch->Draw(m_backGround_Tex.Get(), BACKGROUND_POS);
    // ゲームタイトル
    m_spriteBatch->Draw(m_gameTitle_Tex.Get(), GAMETITLE_POS);
    // 選択文字
    m_spriteBatch->Draw(m_select_Tex.Get(),SELECT_POS);
    // 選択矢印
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_selectArrowPos);
    // iの文字
    m_spriteBatch->Draw(m_i_Tex.Get(), I_POS, nullptr, 
        Colors::White, XMConvertToRadians(m_rotate),I_CENTER_POS);
    // oの文字
    m_spriteBatch->Draw(m_o_Tex.Get(),O_POS, nullptr, 
        Colors::White, XMConvertToRadians(m_rotate), O_CENTER_POS);

    m_spriteBatch->End();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}