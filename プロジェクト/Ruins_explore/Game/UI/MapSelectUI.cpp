/*
    ファイル名：MapSelectUI.cpp
    　　　概要：マップセレクトのUIを管理するクラス
*/
#include "pch.h"
#include "MapSelectUI.h"
#include "Game/Scene/MapSelectScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Data.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MapSelectUI::MapSelectUI(MapSelectScene* mapSelectScene)
    :
    m_mapSelectScene{mapSelectScene},
    m_SelectMenu_Tex{},
    m_selectArrow_Tex{},
    m_tutorialIcon_Tex{},
    m_stage1Icon_Tex{},
    m_selectFlag{},
    m_selectArrowPos{}
{
    // スプライトバッチを設定する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MapSelectUI::~MapSelectUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MapSelectUI::Initialize()
{
    m_SelectMenu_Tex = Resources::GetInstance()->GetTexture(L"SelectMenu");
    m_selectArrow_Tex = Resources::GetInstance()->GetTexture(L"SelectArrow");
    m_tutorialIcon_Tex = Resources::GetInstance()->GetTexture(L"TutorialIcon");
    m_stage1Icon_Tex = Resources::GetInstance()->GetTexture(L"Stage1Icon");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MapSelectUI::Update()
{
    // 選択フラグの処理をする
    SelectFlagProcess();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MapSelectUI::Render()
{
    // 通常のスプライトバッチを開始する
    m_spriteBatch->Begin();

    // 選択メニューを表示する
    m_spriteBatch->Draw(m_SelectMenu_Tex.Get(), SELECTMENU_POS);
    // 選択矢印を表示する
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_selectArrowPos);
    // チュートリアルのアイコンを表示する
    m_spriteBatch->Draw(m_tutorialIcon_Tex.Get(), TUTORIALICON_POS);
    // ステージ1のアイコンを表示する
    m_spriteBatch->Draw(m_stage1Icon_Tex.Get(), STAGE1ICON_POS);

    // 通常のスプライトバッチを終了する
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MapSelectUI::Finalize()
{
   
}

//---------------------------------------------------------
// 選択フラグの処理をする
//---------------------------------------------------------
void MapSelectUI::SelectFlagProcess()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    if (kb->IsKeyPressed((DirectX::Keyboard::Up)))
    {
        if (m_selectFlag == 0)
        {
            m_selectFlag = 1;
        }
        else
        {
            m_selectFlag--;
        }
    }
    if (kb->IsKeyPressed((DirectX::Keyboard::Down)))
    {
        if (m_selectFlag == 1)
        {
            m_selectFlag = 0;
        }
        else
        {
            m_selectFlag++;
        }
    }
    switch (m_selectFlag)
    {
    case 0:
        m_selectArrowPos = SELECTARROW_POS_0;
        break;
    case 1:
        m_selectArrowPos = SELECTARROW_POS_1;
        break;
    default:
        break;
    }

    // 選択フラグごとのシーン遷移の処理
    if (kb->IsKeyPressed((DirectX::Keyboard::Space)))
    {
        switch (m_selectFlag)
        {
        case 0:
            Data::GetInstance()->SetMapSelectStage(0);
            break;
        case 1:
            Data::GetInstance()->SetMapSelectStage(1);
            break;
        default:
            break;
        }
        // プレイシーンに移行
        m_mapSelectScene->ChangeScene();
    }
}
