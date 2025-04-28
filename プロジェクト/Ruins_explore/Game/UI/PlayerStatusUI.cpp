/*
    @file    PlayerStatusUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "PlayerStatusUI.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "PlayerUIManager.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerStatusUI::PlayerStatusUI(Player* player)
    :
    m_player{player},
    m_spriteBatch{},
    m_healthPosition{},
    m_staminaPosition{},
    m_scale{1.f},
    m_hearthRed_Tex{},
    m_hearthGray_Tex{},
    m_staminaYellow_Tex{},
    m_staminaGray_Tex{},
    m_statusIcon_Tex{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerStatusUI::~PlayerStatusUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerStatusUI::Initialize()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;
    // スプライトバッチを取得する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();

    // 画像を読み込む
    m_statusIcon_Tex    = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Status_icon.png");
    m_hearthRed_Tex     = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Health_Red.png");
    m_hearthGray_Tex    = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Health_Gray.png");
    m_staminaYellow_Tex = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Stamina_Yellow.png");
    m_staminaGray_Tex   = Resources::GetInstance()->GetTextureFromFile(L"Resources/Textures/Stamina_Gray.png");

    // 体力表示の位置を設定する
    for (int i = 0; i < m_player->GetMAXHP(); i++)
    {
        m_healthPosition[i] = Vector2(HEALTH_SHIFT_LENGTH * i + HEALTH_POS_ORIGIN.x, HEALTH_POS_ORIGIN.y);
    }
    // スタミナ表示の位置を設定する
    for (int i = 0; i < m_player->GetMAXSTAMINA(); i++)
    {
        m_staminaPosition[i] = Vector2(STAMINA_SHIFT_LENGTH * i + STAMINA_POS_ORIGIN.x, STAMINA_POS_ORIGIN.y);
    }
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerStatusUI::Update()
{
    // 現在のHP割合を計算
    m_scale = static_cast<float>(m_player->GetHP() / m_player->GetMAXHP());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerStatusUI::Render()
{

    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ステータスアイコン
    m_spriteBatch->Draw(m_statusIcon_Tex.Get(), STATUS_ICON_POS);

    // 体力(灰色)
    for (int i = 0; i < m_player->GetMAXHP(); i++)
    {
        m_spriteBatch->Draw(m_hearthGray_Tex.Get(), m_healthPosition[i]);
    }
    // スタミナ(灰色)
    for (int i = 0; i < m_player->GetMAXSTAMINA(); i++)
    {
        m_spriteBatch->Draw(m_staminaGray_Tex.Get(), m_staminaPosition[i]);
    }

    // 体力(赤色)
    for (int i = 0; i < m_player->GetHP(); i++)
    {
        m_spriteBatch->Draw(m_hearthRed_Tex.Get(), m_healthPosition[i]);
    }
    // スタミナ(黄色)
    for (int i = 0; i < m_player->GetStamina(); i++)
    {
        m_spriteBatch->Draw(m_staminaYellow_Tex.Get(), m_staminaPosition[i]);
    }

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerStatusUI::Finalize()
{
   
}