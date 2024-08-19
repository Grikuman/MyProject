/*
	@file	Hand.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Hand.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <GeometricPrimitive.h>
#include <iostream>
#include "Libraries/MyLib/GridFloor.h"
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Hand::Hand()
	:
	m_commonResources{},
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_jumpSpeed{},
	m_rotate{},
	m_isJumping{},
	m_jumpTrigger{},
	m_cameraRotate{}
{
	m_state = Hand::STATE::NONE;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Hand::~Hand()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Hand::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//カメラを作成
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//当たり判定
	m_collision = std::make_unique<Collision>();
	//プレイヤー座標の初期化
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
	//プレイヤーの速度の初期化
	m_speed = DirectX::SimpleMath::Vector3::Zero;
	// ジャンプトリガーを初期化
	m_jumpTrigger = false;
	//カメラの回転値の初期化
	m_cameraRotate = 0.0f;

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerHand.cmo", *fx);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Hand::Update(
	float elapsedTime,
	DirectX::SimpleMath::Vector3 speed,
	DirectX::SimpleMath::Quaternion rotate
)
{
    UNREFERENCED_PARAMETER(elapsedTime);
	m_speed = speed;
    m_world = Matrix::Identity;                                         // 行列の初期化
    m_world *= Matrix::CreateScale(0.004f);
	m_state = Hand::STATE::NONE;

	// Bodyのクォータニオンを取り込む
	m_rotate = rotate;  

	// ジャンプ
	Jump();

    // 座標移動
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // ゲームパッド入力の速度調整で0.1をかけている

	auto kb = m_commonResources->GetInputManager()->GetKeyboardState();
	float r = 0;
	if (kb.F)
	{
		r = 45.f;
		m_state = Hand::STATE::ATTACKING;
	}
	m_world *= Matrix::CreateRotationY(XMConvertToRadians(r));

    // ワールド行列にモデルの位置と回転を反映させる
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Hand::Render(
	DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix proj)
{
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates(); 

    // モデルを描画する
    m_model->Draw(context, *states, m_world, view, proj);
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Hand::Finalize()
{
}

void Hand::OnJumpTrigger()
{
	m_jumpTrigger = true;
}

void Hand::Jump()
{
	DirectX::SimpleMath::Vector3 ground(0.f, 0.f, 0.f);
	float gravity = 0.005f;      // 重力の強さ
	float jumpSpeed = 0.15f;     // ジャンプの初速度
	float maxFallSpeed = 0.2f;   // 最大落下速度

	Vector3 oldpos = m_position; //ジャンプ前の位置

	// ジャンプしていない状態かつトリガーがTRUEならジャンプに移行する
	if (!m_isJumping && m_jumpTrigger)// || !m_isJumping && gp.buttons.a)
	{
		m_jumpSpeed.y = jumpSpeed;
		m_isJumping = true; // ジャンプ中にする
	}
	if (m_isJumping)
	{
		// ジャンプ速度に重力を適用
		m_jumpSpeed.y -= gravity;

		// 落下速度が最大落下速度を超えないようにする
		if (m_jumpSpeed.y < -maxFallSpeed)
		{
			m_jumpSpeed.y = -maxFallSpeed;
		}

		// 位置を更新
		m_position.y += m_jumpSpeed.y;
	}
	// 地面との衝突をチェック
	if (m_collision->CheckGround(
		m_position - DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f),
		ground))
	{
		m_position = oldpos; // ジャンプ前の位置に戻す
		m_isJumping = false; // ジャンプを可能にさせる
		m_jumpTrigger = false; //トリガーを戻す
		m_jumpSpeed.y = 0; // 速度をリセット
	}
}