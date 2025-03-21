/*
    ファイル名：TutorialGuideUI.cpp
    　　　概要：マップセレクトのUIを管理するクラス
*/
#include "pch.h"
#include "TutorialGuideUI.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Data.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TutorialGuideUI::TutorialGuideUI()
    :
    m_guideMissionText_Tex{},
    m_missionCheckMark_Tex{},
    m_missionFlag{},
    m_missionClearCnt{}
{
    // スプライトバッチを設定する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TutorialGuideUI::~TutorialGuideUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TutorialGuideUI::Initialize()
{
    // 画像を取得する
    m_guideMissionText_Tex = Resources::GetInstance()->GetTexture(L"TutorialGuideMissionText");
    m_missionCheckMark_Tex = Resources::GetInstance()->GetTexture(L"MissionCheckMark");

    // ミッションフラグの初期化
    for (int i = 0; i < 4; i++)
    {
        m_missionFlag[i] = false;
    }
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TutorialGuideUI::Update()
{
    m_missionClearCnt = 0;
    // ミッションをクリアした場合、4番目のミッションをクリアする
    for (int i = 0; i < 3; i++)
    {
        if (m_missionFlag[i])
        {
            m_missionClearCnt++;
        }
    }
    // 全てのミッションをクリアしていた場合
    if (m_missionClearCnt == 3)
    {
        m_missionFlag[3] = true;
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TutorialGuideUI::Render()
{
    // 通常のスプライトバッチを開始する
    m_spriteBatch->Begin();

    // 選択メニューを表示する
    m_spriteBatch->Draw(m_guideMissionText_Tex.Get(), GUIDEMISSION_POS);

    for (int i = 0; i < 4; i++)
    {
        if (m_missionFlag[i])
        {
            m_spriteBatch->Draw(m_missionCheckMark_Tex.Get(), MISSIONCHECKMARK_POS[i]);
        }
    }

    // 通常のスプライトバッチを終了する
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TutorialGuideUI::Finalize()
{
   
}