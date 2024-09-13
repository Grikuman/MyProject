/*
    ファイル: PlayerIdling.cpp
    クラス  : プレイヤーアイドリングクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerIdling.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerIdling::PlayerIdling(Player* player, const std::unique_ptr<DirectX::Model>& model)
	:
    m_player(player),
	m_model{ model }
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerIdling::~PlayerIdling()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerIdling::Initialize()
{
	
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerIdling::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    auto kb = Graphics::GetInstance()->GetKeyboardState();

    

    //*======================================================*
    //　処理:プレイヤーの速度設定と移動
    //*======================================================*
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

    // スタミナがある場合
    if (m_player->GetStamina() >= 1)
    {
        if (kb->Space)
        {
            m_player->SetStamina(m_player->GetStamina() - 1); // スタミナを消費
            m_player->ChangeState(m_player->GetPlayerDash()); // ステートをダッシュに変更
        }
    }
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerIdling::Render()
{
    DirectX::SimpleMath::Matrix view, proj;

    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    // プレイヤーの描画
    Matrix world = Matrix::CreateScale(0.4f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
    world *= Matrix::CreateTranslation(m_player->GetPosition());
    m_model->Draw(context, *states, world, view, proj); // モデルを描画する
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerIdling::Finalize()
{
    
}
