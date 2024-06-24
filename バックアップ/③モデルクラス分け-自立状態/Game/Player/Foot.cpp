/*
	@file	Foot.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Foot.h"
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
Foot::Foot()
	:
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_velocity{},
	m_rotate{},
	m_isJumping{},
	m_cameraRotate{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Foot::~Foot()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Foot::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto states = m_commonResources->GetCommonStates();

	//カメラを作成
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//当たり判定
	m_collision = std::make_unique<Collision>();
	//プレイヤー座標の初期化
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
	//プレイヤーの速度の初期化
	m_speed = DirectX::SimpleMath::Vector3::Zero;
	//カメラの回転値の初期化
	m_cameraRotate = 0.0f;

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerFoot.cmo", *fx);


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Foot::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // キーボード
    auto gp = m_commonResources->GetInputManager()->GetGamePadState();  // ゲームパッド
    m_speed = DirectX::SimpleMath::Vector3::Zero;                       // 速度のリセット
    m_world = Matrix::Identity;                                         // 行列の初期化
    m_world *= Matrix::CreateScale(0.004f);
    //*======================================================*
    //　キーボード入力・ゲームパッド入力
    //　処理:クォータニオンでのプレイヤー向き変更
    //      :カメラの回転処理
    //*======================================================*

    // ロール、ピッチ、ヨー
    float roll = 0.0f;  // Ｚ軸回転
    float pitch = 0.0f; // Ｘ軸回転
    float yaw = 0.0f;   // Ｙ軸回転

    float rightX = 0.0f; // yawへ渡す値
    // キーボード入力に基づいてプレイヤーの向きとカメラの回転を設定
    if (kb.Left)
    {
        m_cameraRotate++;
        rightX = 1.0f;
    }
    else if (kb.Right)
    {
        m_cameraRotate--;
        rightX = -1.0f;
    }
    // コントローラー入力に基づいてプレイヤーの向きとカメラの回転を設定
    if (gp.IsConnected())
    {
        rightX = -gp.thumbSticks.rightX;
        m_cameraRotate -= gp.thumbSticks.rightX;
    }
    // ゲームパッドの入力によってyawを変更する
    yaw = XMConvertToRadians(rightX * 1.0f); // 1.0fは適切な倍率に調整
    // クォータニオンをロール、ピッチ、ヨーの値から生成する
    Quaternion q = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
    m_rotate = q * m_rotate;

    //*======================================================*
    //　キーボード入力・ゲームパッド入力
    //　処理:プレイヤーの速度設定と移動
    //*======================================================*
    if (kb.W)
    {
        m_speed.z = -1.f;
    }
    else if (kb.A)
    {
        m_speed.x = -1.f;
    }
    else if (kb.D)
    {
        m_speed.x = 1.f;
    }
    else if (kb.S)
    {
        m_speed.z = 1.f;
    }
    // コントローラー入力に基づいて速度を設定
    if (gp.IsConnected())
    {
        m_speed.x += gp.thumbSticks.leftX;
        m_speed.z -= gp.thumbSticks.leftY; // 左スティックのY軸は上下反転
    }
    //*======================================================*
    //　キーボード入力・ゲームパッド入力
    //　処理:プレイヤーのジャンプ
    //*======================================================*
    DirectX::SimpleMath::Vector3 ground(0.f, 0.f, 0.f);
    float gravity = 0.005f;      // 重力の強さ
    float jumpSpeed = 0.15f;     // ジャンプの初速度
    float maxFallSpeed = 0.2f;   // 最大落下速度

    // ジャンプしていない状態でジャンプ入力を受け付けるとジャンプに移行する
    if (!m_isJumping && kb.Space || !m_isJumping && gp.buttons.a)
    {
        m_velocity.y = jumpSpeed;
        m_isJumping = true;
    }
    if (m_isJumping)
    {
        // ジャンプ速度に重力を適用
        m_velocity.y -= gravity;

        // 落下速度が最大落下速度を超えないようにする
        if (m_velocity.y < -maxFallSpeed)
        {
            m_velocity.y = -maxFallSpeed;
        }

        // 位置を更新
        m_position.y += m_velocity.y;
    }
    // 地面との衝突をチェック
    if (m_collision->CheckGround(m_position + DirectX::SimpleMath::Vector3(0.f, 0.0f, 0.f), ground))
    {
        m_position.y = ground.y;
        m_isJumping = false;
        m_velocity.y = 0; // 速度をリセット
    }

    //*======================================================*
    // 座標移動
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // ゲームパッド入力の速度調整で0.1をかけている
    //カメラの回転行列
    DirectX::SimpleMath::Matrix cameraMatrix;

    cameraMatrix = Matrix::CreateRotationY(XMConvertToRadians(m_cameraRotate));
    //カメラ更新
    m_camera->Update(m_position, cameraMatrix);
    // ワールド行列にモデルの位置と回転を反映させる
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Foot::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_camera->GetViewMatrix();
    proj = m_camera->GetProjectionMatrix();
    Matrix projection = m_camera->GetProjectionMatrix();

    // モデルを描画する
    m_model->Draw(context, *states, m_world, view, proj);
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Foot::Finalize()
{
}