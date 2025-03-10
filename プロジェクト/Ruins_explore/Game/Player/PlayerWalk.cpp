/*
    ファイル名：PlayerWalk.cpp
    　　　概要：プレイヤーの歩行状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerWalk.h"
#include "PlayerDash.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"
#include "Game/Camera/TPS_Camera.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerWalk::PlayerWalk(Player* player)
	:
    m_player(player),
    m_keyHoldTime{}
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
    
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerWalk::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    
    // 歩行処理
    PlayerMove();
    // 歩行からダッシュへ
    WalkToDash();
    // 歩行から攻撃へ
    WalkToAttack();
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
// 歩行処理
//---------------------------------------------------------
void PlayerWalk::PlayerMove()
{
    using namespace DirectX::SimpleMath;
    // キーボード入力を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // 移動処理
    if (kb->W || kb->Up)
    {
        m_player->AddVelocity(Vector3::Forward);
    }
    if (kb->S || kb->Down)
    {
        m_player->AddVelocity(Vector3::Backward);
    }

    // 回転処理
    if(kb->A || kb->Left)
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

    // 移動速度を補正
    m_player->ApplyVelocity(0.05f);

    // 移動させる
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}

//---------------------------------------------------------
// 歩行からダッシュへ
//---------------------------------------------------------
void PlayerWalk::WalkToDash()
{
    // キーボードを取得する
    auto dashKb = InputDevice::GetInstance()->GetKeyboardStateTracker();
    // ダッシュ方向用のキーボードを取得する
    auto directionKb = InputDevice::GetInstance()->GetKeyboardState();
    // ダッシュ方向を設定する
    if (directionKb->W || directionKb->Up)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Forward);
    }
    if (directionKb->S || directionKb->Down)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Backward); 
    }
    if (directionKb->D || directionKb->Right)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Right); 
    }
    if (directionKb->A || directionKb->Left)
    {
        m_player->GetPlayerDash()->SetDashDirection(DirectX::SimpleMath::Vector3::Left); 
    }

    // スタミナがある場合
    if (m_player->GetStamina() >= 1)
    {
        // スペースキーを押したら
        if (dashKb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            // スタミナを消費する
            m_player->SetStamina(m_player->GetStamina() - 1);
            // ステートをダッシュに変更する
            m_player->ChangeState(m_player->GetPlayerDash());
            // ダッシュ音
            Audio::GetInstance()->PlaySE("DashSE");
        }
    }
}

//---------------------------------------------------------
// 歩行から攻撃へ
//---------------------------------------------------------
void PlayerWalk::WalkToAttack()
{
    // キーボードの状態を取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // Fキーが押されているかを確認
    if (kb->IsKeyDown(DirectX::Keyboard::F))
    {
        // 通常パンチに設定する
        m_player->GetPlayerAttack()->ChangeAttackAction(
            m_player->GetPlayerAttack()->GetPlayerNormalPunch());
        // 攻撃へ移行する
        m_player->ChangeState(m_player->GetPlayerAttack());
        // パンチ音
        Audio::GetInstance()->PlaySE("PunchSE");
        // カメラを揺らす
        m_player->GetCamera()->StartShake(0.1f, 0.05f);
    }

    // Cキーが押されているかを確認
    if (kb->IsKeyDown(DirectX::Keyboard::C))
    {
        // 長押しカウントを増加
        m_keyHoldTime++;

        // 長押しが特定の時間（フレーム数）を超えた場合
        if (m_keyHoldTime > 30) // 30フレーム以上
        {
            // チャージパンチになっていなければ
            if (m_player->GetPlayerAttack()->GetCurrentAttackAction() != m_player->GetPlayerAttack()->GetPlayerChargePunch())
            {
                // チャージパンチに変更
                m_player->GetPlayerAttack()->ChangeAttackAction(m_player->GetPlayerAttack()->GetPlayerChargePunch());
            }
            // 攻撃へ移行する
            m_player->ChangeState(m_player->GetPlayerAttack());
            // パンチ音
            Audio::GetInstance()->PlaySE("PunchSE");
            // 長押し時間を0に
            m_keyHoldTime = 0;
        }
    }
    else
    {
        // Cキーが離されたら長押しカウントをリセット
        m_keyHoldTime = 0;
    }
}
