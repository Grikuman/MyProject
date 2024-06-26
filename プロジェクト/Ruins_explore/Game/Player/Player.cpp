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
	
	//プレイヤーの胴体を作成
	m_body = std::make_unique<Body>();
	m_body->Initialize(m_commonResources);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
	// プレイヤーの胴体を更新する
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

NRLib::TPS_Camera* Player::GetCamera()
{
	return m_body->GetCamera();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	return m_body->GetBoundingSphere();
}

bool Player::GetIsAttack()
{
	return m_body->GetIsAttack();
}

