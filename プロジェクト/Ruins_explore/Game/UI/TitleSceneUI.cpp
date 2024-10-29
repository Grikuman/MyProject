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
#include "WorkTool/InputDevice.h"
#include "Game/Scene/TitleScene.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI(TitleScene* titlescene)
    :
    m_ruinsExplorer{},
    m_titleSelect{},
    m_selectIcon{},
    m_i_Rotate{},
    m_o_Rotate{},
    m_titleBackGround{},
    m_black{},
    m_selectPos{},
    m_selectFlag{true},
    m_titleScene{titlescene},
    m_rotate{},
    m_alpha{},
    m_fadeFlag{false},
    m_scale{1.f}
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
    m_ruinsExplorer   = Resources::GetInstance()->GetTexture(L"Ruins_Explorer");
    m_titleSelect     = Resources::GetInstance()->GetTexture(L"TitleSelect");
    m_selectIcon      = Resources::GetInstance()->GetTexture(L"SelectIcon");
    m_i_Rotate        = Resources::GetInstance()->GetTexture(L"i_Rotate");
    m_o_Rotate        = Resources::GetInstance()->GetTexture(L"o_Rotate");
    m_titleBackGround = Resources::GetInstance()->GetTexture(L"TitleBackGround");
    m_black           = Resources::GetInstance()->GetTexture(L"Black");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // 回転
    m_rotate += 1.f;

    //フェードに移行していなければ
    if (!m_fadeFlag)
    {
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
    if (kb->IsKeyPressed(DirectX::Keyboard::Space) && m_selectFlag)
    {
        // フェードフラグをtrue
        m_fadeFlag = true;
    }
    // フェード処理
    if (m_fadeFlag)
    {
        m_alpha += 0.008f;
        m_scale += 0.001f;
        if (m_alpha >= 1.f)
        {
            // アルファ値とスケール値をリセットしておく
            m_alpha = 0.f;
            m_scale = 1.f;
            // シーン遷移
            m_titleScene->ChangeScene();
        }
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    //Matrix matrix = Matrix::CreateTranslation(Vector3(640, 360, 0));
    Matrix matrix = Matrix::CreateScale(m_scale);
    matrix *= Matrix::CreateTranslation(Vector3(0, 0, 0));
    m_spriteBatch->Begin(DirectX::DX11::SpriteSortMode_Deferred,nullptr,nullptr,nullptr,nullptr,nullptr,matrix);
    // 背景
    m_spriteBatch->Draw(m_titleBackGround.Get(), Vector2(0,0));
    m_spriteBatch->End();

    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ステータスアイコン
    m_spriteBatch->Draw(m_ruinsExplorer.Get(), DirectX::SimpleMath::Vector2(350,150));
    // セレクト
    m_spriteBatch->Draw(m_titleSelect.Get(), DirectX::SimpleMath::Vector2(450, 400));
    // セレクトアイコン
    m_spriteBatch->Draw(m_selectIcon.Get(), m_selectPos);
    // i
    m_spriteBatch->Draw(m_i_Rotate.Get(), Vector2(485, 210), nullptr, 
        Colors::White, XMConvertToRadians(m_rotate), Vector2(25, 25));
    // o
    m_spriteBatch->Draw(m_o_Rotate.Get(), Vector2(810, 255), nullptr, 
        Colors::White, XMConvertToRadians(m_rotate), Vector2(25, 25));
    // フェードの色
    Color color = Color(0.0f, 0.0f, 0.0f, m_alpha);
    // 黒のフェード
    m_spriteBatch->Draw(m_black.Get(), Vector2(0,0), color);

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}