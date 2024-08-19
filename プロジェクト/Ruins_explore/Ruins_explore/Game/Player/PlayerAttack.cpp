/*
	@file	PlayerAttack.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <iostream>
#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player)
	:
    m_player(player),
    m_commonResources{},
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_velocity{},
	m_rotate{},
	m_cameraRotate{},
    m_setYaw{},
    m_isAttack{}
{
    m_isAttack = true;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttack::~PlayerAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttack::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//カメラを作成
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//当たり判定クラスを生成
	m_collision = std::make_unique<Collision>();
	//プレイヤー座標の初期化
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    m_speed = DirectX::SimpleMath::Vector3::Zero;                       // 速度のリセット
    m_world = Matrix::Identity;                                         // 行列の初期化
    m_world *= Matrix::CreateScale(0.004f);

    //キー入力：コントローラー入力を受け付けて動作を決める
    InputProcessing();

    //ステートを移行する処理
    //ChangeState();

    //カメラの回転行列を作成する
    DirectX::SimpleMath::Matrix cameraMatrix;
    cameraMatrix = Matrix::CreateRotationY(XMConvertToRadians(m_cameraRotate));
    // カメラを更新する
    m_camera->Update(m_position, cameraMatrix);
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttack::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_camera->GetViewMatrix();
    proj = m_camera->GetProjectionMatrix();

    m_model->Draw(context, *states, m_world, view, proj); // モデルを描画する
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    
}

//---------------------------------------------------------
// キー入力：コントローラー入力を受け付けて動作を決める
//---------------------------------------------------------
void PlayerAttack::InputProcessing()
{
    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // キーボード
    m_isAttack = false;
    //*======================================================*
    //　処理:クォータニオンでのプレイヤー向き変更
    //      :カメラの回転処理
    //*======================================================*

    // ロール、ピッチ、ヨー
    float roll = 0.0f;  // Ｚ軸回転
    float pitch = 0.0f; // Ｘ軸回転
    float yaw = 0.0f;   // Ｙ軸回転

    m_setYaw = 0.0f; //yawへの値を初期化

    // キーボード入力に基づいてプレイヤーの向きとカメラの回転を設定
    if (kb.Left)
    {
        m_cameraRotate++;
        m_setYaw = 1.0f;
    }
    else if (kb.Right)
    {
        m_cameraRotate--;
        m_setYaw = -1.0f;
    }
    // ゲームパッドの入力によってyawを変更する
    yaw = XMConvertToRadians(m_setYaw); // キーボードもゲームパッドも同様に扱う
    // クォータニオンをロール、ピッチ、ヨーの値から生成する
    Quaternion q = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
    m_rotate = q * m_rotate;

    //*======================================================*
    //　処理:プレイヤーの速度設定と移動
    //*======================================================*
    if (kb.W)
    {
        m_speed.z = -1.f;
    }
    if (kb.A)
    {
        m_speed.x = -1.f;
    }
    if (kb.D)
    {
        m_speed.x = 1.f;
    }
    if (kb.S)
    {
        m_speed.z = 1.f;
    }
    
    // 入力後に計算をおこなう
    // 座標移動
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // ゲームパッド入力の速度調整で0.1をかけている
    // ワールド行列にモデルの位置と回転を反映させる
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

// 別の行動へ移行する処理
void PlayerAttack::ChangeState()
{
    auto& kb = m_commonResources->GetInputManager()->GetKeyboardTracker();

    if (kb->IsKeyPressed(DirectX::Keyboard::F))
    {
        m_player->ChangeState(m_player->GetPlayerAttack());
    }
}

DirectX::BoundingSphere PlayerAttack::GetBoundingSphere()
{
    Vector3 center = m_position; // 当たり判定球の中心
    float radius = 0.5f;         // 敵のサイズに応じて調整
    return DirectX::BoundingSphere(center, radius);
}
