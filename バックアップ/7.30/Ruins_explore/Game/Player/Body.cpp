/*
	@file	Body.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Body.h"
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
#include "Hand.h"
#include "Foot.h"

#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Body::Body()
	:
    m_commonResources{},
	m_camera{},
	m_collision{},
	m_model{},
	m_position{},
	m_speed{},
	m_velocity{},
	m_rotate{},
	m_cameraRotate{},
    m_hand{},
    m_foot{},
    m_setYaw{},
    m_isAttack{}
{
    m_state = Body::STATE::NONE; // プレイヤーの初期ステート
    m_isAttack = false;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Body::~Body()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Body::Initialize(CommonResources* resources)
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
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerBody.cmo", *fx);

    // プレイヤーの手を作成
    m_hand = std::make_unique<Hand>();
    m_hand->Initialize(m_commonResources);
    // プレイヤーの足を作成
    m_foot = std::make_unique<Foot>();
    m_foot->Initialize(m_commonResources);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Body::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
    m_speed = DirectX::SimpleMath::Vector3::Zero;                       // 速度のリセット
    m_world = Matrix::Identity;                                         // 行列の初期化
    m_world *= Matrix::CreateScale(0.004f);

    //キー入力：コントローラー入力を受け付けて動作を決める
    InputProcessing();
    
    // 入力後に計算をおこなう
    Calculation();

    //カメラの回転行列を作成する
    DirectX::SimpleMath::Matrix cameraMatrix;
    cameraMatrix = Matrix::CreateRotationY(XMConvertToRadians(m_cameraRotate));
    // カメラを更新する
    m_camera->Update(m_position, cameraMatrix);
    // 手のパーツを更新する
    m_hand->Update(elapsedTime,m_speed,m_rotate);
    // 足のパーツを更新する
    m_foot->Update(elapsedTime,m_speed,m_rotate);
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Body::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_camera->GetViewMatrix();
    proj = m_camera->GetProjectionMatrix();

    m_model->Draw(context, *states, m_world, view, proj); // モデルを描画する

    m_hand->Render(view,proj);                            // 手パーツを描画する
    m_foot->Render(view,proj);                            // 足パーツを描画する
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Body::Finalize()
{
}

//---------------------------------------------------------
// キー入力：コントローラー入力を受け付けて動作を決める
//---------------------------------------------------------
void Body::InputProcessing()
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
    //*======================================================*
    //　キーボード入力・ゲームパッド入力
    //　処理:プレイヤーのジャンプ
    //*======================================================*
    DirectX::SimpleMath::Vector3 ground(0.f, 0.f, 0.f);
    float gravity = 0.005f;      // 重力の強さ
    float jumpSpeed = 0.15f;     // ジャンプの初速度
    float maxFallSpeed = 0.2f;   // 最大落下速度

    Vector3 oldpos = m_position; //ジャンプ前の位置を保存しておく

    // ジャンプしていない状態でジャンプ入力を受け付けるとジャンプに移行する
    if (m_state == STATE::NONE && kb.Space)
    {
        m_velocity.y = jumpSpeed;      // 初速度を加える
        m_state = STATE::JUMPING;      // ジャンプ中にする
        m_hand->OnJumpTrigger();       // 手パーツをジャンプさせる
        m_foot->OnJumpTrigger();       // 足パーツをジャンプさせる
    }
    //ジャンプ中の処理
    if (m_state == STATE::JUMPING)
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
    if (m_collision->CheckGround(
        m_position - DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f),
        ground))
    {
        m_position = oldpos; // ジャンプ前の位置に戻す
        m_state = STATE::NONE; // ジャンプ中ではなくなる
        m_velocity.y = 0; // 速度をリセット
    }
    // 
    if (m_hand->GetState() == Hand::STATE::ATTACKING)
    {
        m_isAttack = true;
    }
}

//---------------------------------------------------------
// 入力後に計算をおこなう
//---------------------------------------------------------
void Body::Calculation()
{
    // 座標移動
    m_position += Vector3::Transform(m_speed, m_rotate) * 0.1f; // ゲームパッド入力の速度調整で0.1をかけている
    // ワールド行列にモデルの位置と回転を反映させる
    m_world *= Matrix::CreateFromQuaternion(m_rotate) * Matrix::CreateTranslation(m_position);
}

DirectX::BoundingSphere Body::GetBoundingSphere()
{
    Vector3 center = m_position; // 当たり判定球の中心
    float radius = 0.5f;         // 敵のサイズに応じて調整
    return DirectX::BoundingSphere(center, radius);
}
