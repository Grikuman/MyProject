/*
    ファイル名：PlayerJump.cpp
    　　　概要：プレイヤーのジャンプ状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerJump.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerJump::PlayerJump(Player* player)
	:
    m_player(player),
    m_jumpTime{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerJump::~PlayerJump()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerJump::Initialize()
{
    // ダッシュ時間を設定
    m_jumpTime = JUMP_TIME;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerJump::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // ダッシュする
    Jump();

    // ダッシュから歩行へ
    JumpToWalk(); 
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerJump::Render()
{
   
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerJump::Finalize()
{
    
}

//---------------------------------------------------------
// ダッシュ処理
//---------------------------------------------------------
void PlayerJump::Jump()
{
    using namespace DirectX::SimpleMath;
    
    Vector3 playerPos = m_player->GetPosition();
    
    m_player->SetPosition(Vector3(playerPos.x, playerPos.y + m_jumpTime * 0.1f, playerPos.z));
}

//---------------------------------------------------------
// 移動処理
//---------------------------------------------------------
void PlayerJump::Move()
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
// ジャンプから歩行へ
//---------------------------------------------------------
void PlayerJump::JumpToWalk()
{
    m_jumpTime--;
    if (m_jumpTime <= 0)
    {
        m_jumpTime = JUMP_TIME;
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}