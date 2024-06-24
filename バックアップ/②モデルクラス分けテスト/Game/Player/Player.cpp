/*
	@file	Player.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/GridFloor.h"
#include "WorkTool/Collision.h"
#include "Body.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_collision{},
	m_body{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Player::~Player()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Player::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto states = m_commonResources->GetCommonStates();
	
	m_body = std::make_unique<Body>();
	m_body->Initialize(m_commonResources);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
	m_body->Update(elapsedTime);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render()
{
    // プレイヤーの胴体を描画する
	m_body->Render();
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Player::Finalize()
{
	m_body->Finalize();
}