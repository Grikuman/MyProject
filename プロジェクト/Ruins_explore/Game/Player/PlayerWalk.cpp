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
    if (kb->A || kb->Left)
    {
        m_player->AddRotation(2.0f);  // 左回転
    }
    if (kb->D || kb->Right)
    {
        m_player->AddRotation(-2.0f); // 右回転
    }

    // 移動速度を補正
    m_player->ApplyVelocity(0.05f);

    // クォータニオンを用いて移動
    Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(m_player->GetAngle()));
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), rotation));
}

//---------------------------------------------------------
// 歩行からダッシュへ
//---------------------------------------------------------
void PlayerWalk::WalkToDash()
{
    // キーボードを取得する
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // スタミナがある場合
    if (m_player->GetStamina() >= 1)
    {
        // スペースキーを押したら
        if (dashkb->IsKeyPressed(DirectX::Keyboard::Space))
        {
            // スタミナを消費する
            m_player->SetStamina(m_player->GetStamina() - 1);
            // ステートをダッシュに変更する
            m_player->ChangeState(m_player->GetPlayerDash());
        }
    }
}

//---------------------------------------------------------
// 歩行から攻撃へ
//---------------------------------------------------------
void PlayerWalk::WalkToAttack()
{
    // キーボードを取得する
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

    // Fキーを押したら
    if (dashkb->IsKeyPressed(DirectX::Keyboard::F))
    {
        // ステートを攻撃に変更する
        m_player->ChangeState(m_player->GetPlayerAttack());
    }
}
