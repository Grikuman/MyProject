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
	m_currentState{},
	m_model{},
	m_camera{},
	m_velocity{},
	m_playerAngle{}
{
	//プレイヤー座標の初期化
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
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

	//D3Dデバイスを取得
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);

	//カメラを作成
	m_camera = std::make_unique<NRLib::TPS_Camera>();

	//プレイヤーのステートを作成
	m_playerIdling = std::make_unique<PlayerIdling>(this,m_model);
	m_playerIdling->Initialize(resources);
	m_playerAttack = std::make_unique<PlayerAttack>(this,m_model);
	m_playerAttack->Initialize(resources);
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// 速度を初期化
	m_velocity = Vector3::Zero;

	//現在のステートを更新する
	m_currentState->Update(elapsedTime);

	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));

	// 移動量を補正する
	m_velocity *= 0.05f;

	// 回転を加味して実際に移動する
	m_position += Vector3::Transform(m_velocity, matrix);

	// カメラを更新する
	m_camera->Update(m_position, matrix);
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
	return m_camera.get();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	Vector3 center = m_position; // 当たり判定球の中心
	float radius = 0.5f;         // サイズに応じて調整
	return DirectX::BoundingSphere(center, radius);
}

bool Player::GetIsAttack()
{
	
	return true;
}

void Player::ChangeState(IState* newState)
{
	m_currentState = newState;
}