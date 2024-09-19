/*
    @file    PlayerStatusUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "PlayerStatusUI.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "PlayerUIManager.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerStatusUI::PlayerStatusUI(Player* player)
    :
    m_player{player},
    m_healthPosition{},
    m_backPosition{},
    m_framePosition{},
    m_staminaPosition{},
    m_scale{1.f},
    m_matrix{},
    m_tex_HealthRed{},
    m_tex_HealthGray{},
    m_tex_StaminaYellow{},
    m_tex_StaminaGray{},
    m_tex_StatusIcon{},
    m_tex_HelthGaugeFrame{}
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
    // スタミナの位置を設定する
    for (int i = 0; i < m_player->GetMAXHP(); i++)
    {
        m_healthPosition[i] = Vector2(53.f * i + 108.f, 600.f);
    }
    // スタミナの位置を設定する
    for (int i = 0; i < m_player->GetMAXSTAMINA(); i++)
    {
        m_staminaPosition[i] = Vector2(50.f * i + 130.f, 660.f);
    }
    // ステータスアイコンの位置を設定する
    m_backPosition = Vector2(10.f,600.f);
    // ゲージの枠の位置を設定する
    m_framePosition = Vector2(120.f, 610.f);

    // 画像を読み込む
    m_tex_StatusIcon            = Resources::GetInstance()->GetTexture(L"Status_Icon");

    for (int i = 0; i < 6; i++)
    {
        m_tex_HealthRed[i]      = Resources::GetInstance()->GetTexture(L"Health_Red");
        m_tex_HealthGray[i]     = Resources::GetInstance()->GetTexture(L"Health_Gray");
        m_tex_StaminaYellow[i]  = Resources::GetInstance()->GetTexture(L"Stamina_Yellow");
        m_tex_StaminaGray[i]    = Resources::GetInstance()->GetTexture(L"Stamina_Gray");
    }

    // スプライトバッチを設定する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
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

    // ステータスアイコンを描画する
    m_spriteBatch->Draw(m_tex_StatusIcon.Get(), m_backPosition);

    // 体力(灰色)
    for (int i = 0; i < m_player->GetMAXHP(); i++)
    {
        m_spriteBatch->Draw(m_tex_HealthGray[i].Get(), m_healthPosition[i]);
    }
    // スタミナ(灰色)
    for (int i = 0; i < m_player->GetMAXSTAMINA(); i++)
    {
        m_spriteBatch->Draw(m_tex_StaminaGray[i].Get(), m_staminaPosition[i]);
    }

    // 体力(赤色)
    for (int i = 0; i < m_player->GetHP(); i++)
    {
        m_spriteBatch->Draw(m_tex_HealthRed[i].Get(), m_healthPosition[i]);
    }
    // スタミナ(黄色)
    for (int i = 0; i < m_player->GetStamina(); i++)
    {
        m_spriteBatch->Draw(m_tex_StaminaYellow[i].Get(), m_staminaPosition[i]);
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