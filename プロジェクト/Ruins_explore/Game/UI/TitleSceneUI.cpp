/*
    @file    TitleSceneUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "TitleSceneUI.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI()
    :
    m_ruinsExplorer{},
    m_titleSelect{},
    m_selectIcon{},
    m_selectPos{},
    m_selectFlag{true},
    m_changeSceneFlag{false}
{
    
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
    // スプライトバッチを設定する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
    // 画像読み込み
    m_ruinsExplorer = Resources::GetInstance()->GetTexture(L"Ruins_Explorer");
    m_titleSelect = Resources::GetInstance()->GetTexture(L"TitleSelect");
    m_selectIcon = Resources::GetInstance()->GetTexture(L"SelectIcon");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // キーボードを取得する
    auto kb = Graphics::GetInstance()->GetKeyboardStateTracker();

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
        m_selectPos = Vector2(500, 390);
    }
    else
    {
        m_selectPos = Vector2(500, 510);
    }

    // シーン遷移
    if (m_selectFlag)
    {
        if (kb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            m_changeSceneFlag = true;
        }
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ステータスアイコンを描画する
    m_spriteBatch->Draw(m_ruinsExplorer.Get(), DirectX::SimpleMath::Vector2(350,150));
    m_spriteBatch->Draw(m_titleSelect.Get(), DirectX::SimpleMath::Vector2(450, 400));
    m_spriteBatch->Draw(m_selectIcon.Get(), m_selectPos);

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}