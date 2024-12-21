/*
    ファイル名：PlayerWalk.cpp
    　　　概要：プレイヤーの歩行状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerWalk.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerWalk::PlayerWalk(Player* player)
	:
    m_player(player),
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerWalk::~PlayerWalk()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerWalk::Initialize()
{
    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Player");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerWalk::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    
    // プレイヤー入力
    PlayerMove();

    // キーボードを取得する
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // スタミナがある場合
    if (m_player->GetStamina() >= 1)
    {
        // スペースキーを押したら
        if (dashkb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            m_player->SetStamina(m_player->GetStamina() - 1); // スタミナを消費
            m_player->ChangeState(m_player->GetPlayerDash()); // ステートをダッシュに変更
        }
    }
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerWalk::Render()
{
    
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerWalk::Finalize()
{
    
}

//---------------------------------------------------------
// プレイヤー入力
//---------------------------------------------------------
void PlayerWalk::PlayerMove()
{
    auto kb = InputDevice::GetInstance()->GetKeyboardState();
    if (kb->W)
    {
        m_player->SetVelocity(Vector3::Forward);         // 移動
    }
    if (kb->A)
    {
        m_player->SetAngle(m_player->GetAngle() + 2.0f); // 回転
    }
    if (kb->S)
    {
        m_player->SetVelocity(Vector3::Backward);        // 移動
    }
    if (kb->D)
    {
        m_player->SetAngle(m_player->GetAngle() - 2.0f); // 回転
    }
    if (kb->Up)
    {
        m_player->SetVelocity(Vector3::Forward);         // 移動
    }
    if (kb->Left)
    {
        m_player->SetAngle(m_player->GetAngle() + 2.0f); // 回転
    }
    if (kb->Down)
    {
        m_player->SetVelocity(Vector3::Backward);        // 移動
    }
    if (kb->Right)
    {
        m_player->SetAngle(m_player->GetAngle() - 2.0f); // 回転
    }
}
