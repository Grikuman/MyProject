/*
    @file    TitleSceneUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "ResultSceneUI.h"
#include "Game/Scene/ResultScene.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultSceneUI::ResultSceneUI(ResultScene* result)
    :
    m_selectIcon{},
    m_clear{},
    m_dead{},
    m_resultClear{},
    m_resultDead{},
    m_black{},
    m_pushSpaceKey{},
    m_selectPos{},
    m_selectFlag{true},
    m_alpha{1.0f},
    m_spaceAlpha{1.0f},
    m_fadeFlag{false},
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
    m_selectIcon      = Resources::GetInstance()->GetTexture(L"SelectIcon");
    m_clear           = Resources::GetInstance()->GetTexture(L"Clear");
    m_dead            = Resources::GetInstance()->GetTexture(L"Dead");;
    m_resultClear     = Resources::GetInstance()->GetTexture(L"ResultClear");;
    m_resultDead      = Resources::GetInstance()->GetTexture(L"ResultDead");
    m_black           = Resources::GetInstance()->GetTexture(L"Black");
    m_pushSpaceKey    = Resources::GetInstance()->GetTexture(L"PushSpaceKey");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultSceneUI::Update()
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
        m_selectPos = Vector2(500, 390);
    }
    else
    {
        m_selectPos = Vector2(500, 510);
    }

    // フェードイン処理
    if (m_alpha >= 0)
    {
        m_alpha -= 0.008f;
    }
    // 点滅の速度を設定
    float blinkSpeed = 5.0f; // 1秒間に1回点滅
    // 時間加算
    m_time += 0.016f;
    // sin関数を使って、0から1の間で変化させる
    m_spaceAlpha = (sin(m_time * blinkSpeed) + 1) / 2; // 0-1の範囲に収める
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultSceneUI::Render()
{
    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ＜ リザルト結果で表示を変更する ＞
    if (Data::GetInstance()->GetPlaySceneResult()) // 生存
    {
        m_spriteBatch->Draw(m_resultClear.Get(), Vector2(0, 0));
        m_spriteBatch->Draw(m_clear.Get(), Vector2(200, 50));
    }
    else // 死亡
    {
        m_spriteBatch->Draw(m_resultDead.Get(), Vector2(0, 0));
        m_spriteBatch->Draw(m_dead.Get(), Vector2(200, 50));
    }
    // スペースキーのフェードカラー
    Color spacecolor = Color(0.9f, 0.9f, 0.9f, m_spaceAlpha);
    // スペースキー
    m_spriteBatch->Draw(m_pushSpaceKey.Get(), Vector2(400, 580),spacecolor);

    // フェードの色
    Color color = Color(0.0f, 0.0f, 0.0f, m_alpha);
    // 黒のフェード
    m_spriteBatch->Draw(m_black.Get(), Vector2(0, 0), color);

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultSceneUI::Finalize()
{
   
}