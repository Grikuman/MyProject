/*
	@file	PlayerDash.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerDash.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerDash::PlayerDash(Player* player, const std::unique_ptr<DirectX::Model>& model)
	:
    m_player(player),
    m_commonResources{},
	m_model{ model },
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
void PlayerDash::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

    // ダッシュ時間を設定
    m_dashTime = DASHTIME;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerDash::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    m_player->SetVelocity(Vector3::Forward * 5.f);
    m_dashTime--;
    if (m_dashTime <= 0.f)
    {
        m_dashTime = DASHTIME;
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerDash::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_player->GetCamera()->GetViewMatrix();
    proj = m_player->GetCamera()->GetProjectionMatrix();

    // プレイヤーの描画
    Matrix world = Matrix::CreateScale(0.4f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
    world *= Matrix::CreateTranslation(m_player->GetPosition());
    m_model->Draw(context, *states, world, view, proj); // モデルを描画する
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerDash::Finalize()
{
    
}
