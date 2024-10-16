/*
    ファイル: PlayerIdling.cpp
    クラス  : プレイヤーアイドリングクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerIdling.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerIdling::PlayerIdling(Player* player)
	:
    m_player(player),
	m_model{}
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
    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Player");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerIdling::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // キーボードを取得する
    auto kb = InputDevice::GetInstance()->GetKeyboardState();
    auto dashkb = InputDevice::GetInstance()->GetKeyboardStateTracker();

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
void PlayerIdling::Render()
{
    // コンテキスト・ステートを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    // ビュー・プロジェクションを取得する
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    // プレイヤーの描画
    Matrix world = Matrix::CreateScale(1.f);
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
