/*
    ファイル名：PlayerDash.cpp
    　　　概要：プレイヤーのダッシュ状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerDash.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerDash::PlayerDash(Player* player)
	:
    m_player(player),
    m_nowDirection{DirectX::SimpleMath::Vector3::Backward},
    m_dashTime{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerDash::~PlayerDash()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerDash::Initialize()
{
    // ダッシュ時間を設定
    m_dashTime = DASHTIME;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerDash::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // ダッシュする
    Dash();
    // ダッシュから歩行へ
    DashToWalk(); 
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerDash::Render()
{
   
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerDash::Finalize()
{
    
}

//---------------------------------------------------------
// ダッシュ処理
//---------------------------------------------------------
void PlayerDash::Dash()
{
    // 移動処理(入力方向に動く)
    m_player->AddVelocity(m_nowDirection * 4.0f);
    // 移動速度を補正
    m_player->ApplyVelocity(0.05f);
    // クォータニオンを用いて移動
    m_player->SetPosition(m_player->GetPosition() + DirectX::SimpleMath::Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// ダッシュから歩行へ
//---------------------------------------------------------
void PlayerDash::DashToWalk()
{
    // ダッシュ時間の管理
    m_dashTime--;
    if (m_dashTime <= 0.0f)
    {
        m_dashTime = DASHTIME;
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}

//---------------------------------------------------------
// ダッシュから攻撃へ
//---------------------------------------------------------
void PlayerDash::DashToAttack()
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    if (kb->F)
    {
        // 攻撃へ移行する
        m_player->ChangeState(m_player->GetPlayerAttack());
    }
}