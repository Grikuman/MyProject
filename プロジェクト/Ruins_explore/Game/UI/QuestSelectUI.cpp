/*
    ファイル名：QuestSelectUI.cpp
    　　　概要：マップセレクトのUIを管理するクラス
*/
#include "pch.h"
#include "QuestSelectUI.h"
#include "Game/Scene/QuestSelectScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
QuestSelectUI::QuestSelectUI()
    :
    m_SelectMenu_Tex{},
    m_selectArrow_Tex{},
    m_tutorialIcon_Tex{},
    m_stage1Icon_Tex{},
    m_questPopup_Tex{},
    m_selectFlag{},
    m_questArrowPos{},
    m_popupArrowPos{},
    m_popupViewFlag{false},
    m_popupFlag{false},
    m_questStart{false}
{
    // スプライトバッチを設定する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
QuestSelectUI::~QuestSelectUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void QuestSelectUI::Initialize()
{
    // 画像を取得する
    m_SelectMenu_Tex = Resources::GetInstance()->GetTexture(L"SelectMenu");
    m_selectArrow_Tex = Resources::GetInstance()->GetTexture(L"SelectArrow");
    m_tutorialIcon_Tex = Resources::GetInstance()->GetTexture(L"TutorialIcon");
    m_stage1Icon_Tex = Resources::GetInstance()->GetTexture(L"Stage1Icon");
    m_questPopup_Tex = Resources::GetInstance()->GetTexture(L"QuestPopup");
    m_questBoard_Tex[0] = Resources::GetInstance()->GetTexture(L"QuestBoard0");
    m_questBoard_Tex[1] = Resources::GetInstance()->GetTexture(L"QuestBoard1");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void QuestSelectUI::Update()
{
    // 選択フラグの処理をする
    SelectFlagProcess();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void QuestSelectUI::Render()
{
    // 通常のスプライトバッチを開始する
    m_spriteBatch->Begin();

    // 選択メニューを表示する
    m_spriteBatch->Draw(m_SelectMenu_Tex.Get(), SELECTMENU_POS);
    // クエスト選択矢印を表示する
    m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_questArrowPos);
    // チュートリアルのアイコンを表示する
    m_spriteBatch->Draw(m_tutorialIcon_Tex.Get(), TUTORIALICON_POS);
    // ステージ1のアイコンを表示する
    m_spriteBatch->Draw(m_stage1Icon_Tex.Get(), STAGE1ICON_POS);
    // クエストボードを表示する
    m_spriteBatch->Draw(m_questBoard_Tex[m_selectFlag].Get(), QUEST_BOARD_POS);

    // 通常のスプライトバッチを終了する
    m_spriteBatch->End();

    // ポップアップの描画をする
    PopupRender();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void QuestSelectUI::Finalize()
{
   
}

//---------------------------------------------------------
// 選択フラグの処理をする
//---------------------------------------------------------
void QuestSelectUI::SelectFlagProcess()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // * フラグごとによって選択矢印の位置を決定する *
    // クエスト選択画面の矢印の位置
    m_questArrowPos = ARROW_POS[m_selectFlag];
    // ポップアップ画面の矢印の位置
    if (m_popupFlag) // はい
    {
        m_popupArrowPos = POPUP_ARROW_POS[0];
    }
    else             // いいえ
    {
        m_popupArrowPos = POPUP_ARROW_POS[1];
    }

    // * クエストを選択する操作 *
    // ポップアップが出ていない状態でのみ操作可能
    if (!m_popupViewFlag)
    {
        // クエストを選択する操作
        if (kb->IsKeyPressed((DirectX::Keyboard::Up)))  // 上に移動
        {
            if (m_selectFlag == 0)
            {
                m_selectFlag = 1;
            }
            else
            {
                m_selectFlag--;
            }
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }
        if (kb->IsKeyPressed((DirectX::Keyboard::Down))) // 下に移動
        {
            if (m_selectFlag == 1)
            {
                m_selectFlag = 0;
            }
            else
            {
                m_selectFlag++;
            }
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }

        // クエストを選択し、ポップアップ操作を可能にする
        if (kb->IsKeyPressed((DirectX::Keyboard::Space)))
        {
            m_popupViewFlag = true;
            Audio::GetInstance()->PlaySE("QuestSelectSE2");
            return;
        }
    }

    // * ポップアップ内の操作 *
    // ポップアップが出ている状態でのみ操作可能
    if (m_popupViewFlag)
    {
        // ポップアップ内での選択操作
        if (kb->IsKeyPressed((DirectX::Keyboard::Left)))  // はい
        {
            m_popupFlag = true;
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }
        if (kb->IsKeyPressed((DirectX::Keyboard::Right))) // いいえ
        {
            m_popupFlag = false;
            Audio::GetInstance()->PlaySE("QuestSelectSE1");
        }

        // ポップアップ内でのフラグ処理
        if (kb->IsKeyPressed((DirectX::Keyboard::Space)))
        {
            // はい　を選んでいる場合はステージを決定する
            if (m_popupFlag)
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
                // クエストを開始する
                m_questStart = true;
            }
            // いいえ　を選んでいる場合はクエスト選択に戻る
            else
            {
                // ポップアップを閉じてクエスト選択に戻る
                m_popupViewFlag = false;
                Audio::GetInstance()->PlaySE("QuestSelectSE3");
                return;
            }
        }
    }
}

//---------------------------------------------------------
// ポップアップ内での描画をする
//---------------------------------------------------------
void QuestSelectUI::PopupRender()
{
    // ポップアップの表示フラグがtrueならばポップアップを表示する
    if (m_popupViewFlag)
    {
        // 通常のスプライトバッチを開始する
        m_spriteBatch->Begin();

        // ポップアップを表示する
        m_spriteBatch->Draw(m_questPopup_Tex.Get(), POPUP_POS);
        // ポップアップ内での矢印を表示する
        m_spriteBatch->Draw(m_selectArrow_Tex.Get(), m_popupArrowPos);

        // 通常のスプライトバッチを終了する
        m_spriteBatch->End();
    }
}
