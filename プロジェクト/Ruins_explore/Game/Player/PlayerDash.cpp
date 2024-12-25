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
// ダッシュ処理
//---------------------------------------------------------
void PlayerDash::Dash()
{
    using namespace DirectX::SimpleMath;
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // プレイヤー入力
    if (kb->A || kb->Left)
    {
        // Y軸を中心に左回転を加算
        Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(3.0f));
        m_player->AddAngle(rotation);
    }
    if (kb->D || kb->Right)
    {
        // Y軸を中心に右回転を加算
        Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(-3.0f));
        m_player->AddAngle(rotation);
    }

    // 現在の角度を取得
    Quaternion angle = m_player->GetAngle(); 
    angle.Normalize(); 
    // 正規化後の角度を設定
    m_player->SetAngle(angle); 

    // 移動処理
    m_player->AddVelocity(Vector3::Forward * 4.0f);
    // 移動速度を補正
    m_player->ApplyVelocity(0.05f);

    // クォータニオンを用いて移動
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));

    // ダッシュから歩行へ
    DashToWalk();
}

//---------------------------------------------------------
// ダッシュから歩行へ
//---------------------------------------------------------
void PlayerDash::DashToWalk()
{
    // ダッシュ時間の管理
    m_dashTime--;
    if (m_dashTime <= 0.f)
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

//using namespace DirectX::SimpleMath;
//auto kb = InputDevice::GetInstance()->GetKeyboardState();
//
//// プレイヤー入力
//if (kb->A || kb->Left)
//{
//    m_player->AddRotation(3.0f); // 回転
//}
//if (kb->D || kb->Right)
//{
//    m_player->AddRotation(-3.0f); // 回転
//}
//
//// 真っ直ぐ進む
//m_player->AddVelocity(Vector3::Forward * 4.f);
//// ダッシュ時間を減少させる
//m_dashTime--;
//
//// ダッシュ時間が終了した場合
//if (m_dashTime <= 0.f)
//{
//    // ダッシュ時間をリセットする
//    m_dashTime = DASHTIME;
//    // アイドリング状態へ移行する
//    m_player->ChangeState(m_player->GetPlayerWalk());
//}
//
//// 移動速度を補正
//m_player->ApplyVelocity(0.05f);
//
//// クォータニオンを用いて移動
//m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));