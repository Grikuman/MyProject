/*
    ファイル名：PlayerDash.cpp
    　　　概要：プレイヤーのダッシュ状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerDash.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerDash::PlayerDash(Player* player)
	:
    m_player(player),
	m_model{},
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
    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Player");
    // ダッシュ時間を設定
    m_dashTime = DASHTIME;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerDash::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    
    // プレイヤー入力
    PlayerInput();

    // ダッシュする
    Dash();
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
// プレイヤー入力
//---------------------------------------------------------
void PlayerDash::PlayerInput()
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // プレイヤー入力
    if (kb->A)
    {
        m_player->SetAngle(m_player->GetAngle() + 3.0f); // 回転
    }
    if (kb->D)
    {
        m_player->SetAngle(m_player->GetAngle() - 3.0f); // 回転
    }
}

//---------------------------------------------------------
// ダッシュ処理
//---------------------------------------------------------
void PlayerDash::Dash()
{
    // 真っ直ぐ進む
    m_player->SetVelocity(Vector3::Forward * 4.f);
    // ダッシュ時間を減少させる
    m_dashTime--;

    // ダッシュ時間が終了した場合
    if (m_dashTime <= 0.f)
    {
        // ダッシュ時間をリセットする
        m_dashTime = DASHTIME;
        // アイドリング状態へ移行する
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}
