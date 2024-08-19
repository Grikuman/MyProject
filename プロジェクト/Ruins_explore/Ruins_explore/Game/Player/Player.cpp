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
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_playerIdling{},
	m_playerAttack{},
	m_currentState{}
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

	//プレイヤーのステートを作成
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	m_playerIdling->Initialize(resources);
	m_playerAttack = std::make_unique<PlayerAttack>(this);
	m_playerAttack->Initialize(resources);
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// プレイヤーのステートを更新する
	m_currentState->Update(elapsedTime);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render()
{
	// プレイヤーのステートを描画する
	m_currentState->Render();
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Player::Finalize()
{
	m_playerIdling.reset();
	m_playerAttack.reset();
}

NRLib::TPS_Camera* Player::GetCamera()
{
	return m_currentState->GetCamera();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	return m_currentState->GetBoundingSphere();
}

bool Player::GetIsAttack()
{
	if (m_currentState == m_playerAttack.get())
	{
		return true;
	}
	return false;
}

void Player::ChangeState(IState* newState)
{
	m_currentState = newState;
}