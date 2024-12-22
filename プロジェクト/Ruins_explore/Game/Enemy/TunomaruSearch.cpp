/*
    ファイル名：TunomaruSearch.cpp
    　　　概要：つのまるの索敵状態を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruSearch.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruSearch::TunomaruSearch(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruSearch::~TunomaruSearch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruSearch::Initialize()
{
    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruSearch::Update()
{
    // プレイヤーとの距離を計算
    DirectX::SimpleMath::Vector3 playerPosition = m_tunomaru->GetPlayer()->GetPosition();
    DirectX::SimpleMath::Vector3 direction = playerPosition - m_tunomaru->GetPosition();
    float distance = direction.Length();  // プレイヤーとの距離

    // 距離が15以内なら追いかける
    if (distance <= 20.0f)
    {
        // 追いかける方向に向かう
        direction.Normalize();  // 単位ベクトルに正規化

        // プレイヤーの方向に向かって回転角度を計算
        float targetAngle = XMConvertToDegrees(atan2(direction.x, direction.z));

        // 現在の角度との差を計算して回転速度を加算
        float angleDiff = targetAngle - m_tunomaru->GetAngle();
        if (angleDiff > 180.0f) angleDiff -= 360.0f;  // 角度差が180度以上なら補正
        if (angleDiff < -180.0f) angleDiff += 360.0f;

        // 回転速度を加算して角度を更新
        //m_angle += angleDiff * 0.1f;  // 0.1fで回転の速さを調整
        m_tunomaru->AddRotation(angleDiff * -0.1f);

        // プレイヤー方向に移動
        //m_velocity += direction * 1.0f;  // プレイヤー方向へ速度を加算
        m_tunomaru->AddVelocity(direction * 1.0f);

        // 移動速度を補正
        //m_velocity *= 0.05f;
        m_tunomaru->ApplyVelocity(0.03f);

        // 移動量を計算
        DirectX::SimpleMath::Quaternion movementRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, XMConvertToRadians(m_tunomaru->GetAngle()));
        DirectX::SimpleMath::Vector3 movement = DirectX::SimpleMath::Vector3::Transform(m_tunomaru->GetVelocity(), movementRotation);  // 回転後の移動量

        // 位置更新
        //m_position += movement;
        m_tunomaru->SetPotision(m_tunomaru->GetPosition() + movement);
    }
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruSearch::Finalize()
{
    
}

//
//// プレイヤーの位置を取得する
//Vector3 playerPos = m_tunomaru->GetPlayer()->GetPosition();
//// つのまるの現在の位置を取得する
//Vector3 tunomaruPos = m_tunomaru->GetPosition();
//// プレイヤーとの距離を計算する
//float distance = Vector3::Distance(playerPos, tunomaruPos);
//
//// 距離が10.f以内ならアタック状態へ移行する
//if (distance < 5.0f)
//{
//    // プレイヤーへの向きを計算する
//    Vector3 direction = playerPos - tunomaruPos;
//    direction.Normalize();
//    float newAngle = atan2f(-direction.x, -direction.z);
//    m_tunomaru->SetAngle(XMConvertToDegrees(newAngle));
//    // アタック状態へ移行する
//    m_tunomaru->ChangeState(m_tunomaru->GetTunomaruAttack());
//    return;
//}
//
//// 2秒おきのランダム移動を管理するタイマー
//static float randomMoveTimer = 0.0f;
//randomMoveTimer += 1.0f / 60.0f;
//
//// 距離が20.f以内ならプレイヤーを追いかける
//if (distance < 20.0f)
//{
//    Vector3 direction = playerPos - tunomaruPos;
//    direction.Normalize();
//    float newAngle = atan2f(-direction.x, -direction.z);
//    m_tunomaru->SetAngle(XMConvertToDegrees(newAngle));
//    m_tunomaru->SetPotision(tunomaruPos + direction * 0.01f);
//}
//else
//{
//    // 2秒ごとにランダムな方向に移動
//    if (randomMoveTimer >= 2.0f)
//    {
//        randomMoveTimer = 0.0f; // Reset the timer
//
//        // ランダムな方向を生成する
//        float randomAngle = static_cast<float>(rand() % 360); // 0から360度のランダムな角度
//        Vector3 randomDirection = Vector3(sinf(randomAngle), 0, cosf(randomAngle));
//
//        // つのまるの角度を更新する
//        m_tunomaru->SetAngle(randomAngle);
//        m_tunomaru->SetVelocity(randomDirection * 0.1f); // 適切な速度でランダムに移動
//
//        // ランダムな方向に移動
//        m_tunomaru->SetPotision(tunomaruPos + randomDirection * 0.1f);
//    }
//}void Tunomaru::Render()
//{
//    DirectX::SimpleMath::Matrix view, proj;
//    // リソースを取得する
//    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
//    auto states = Graphics::GetInstance()->GetCommonStates();
//    view = Graphics::GetInstance()->GetViewMatrix();
//    proj = Graphics::GetInstance()->GetProjectionMatrix();
//
//    // ワールド行列
//    Matrix world = Matrix::CreateScale(1.f);
//    world *= Matrix::CreateRotationY(XMConvertToRadians(m_angle));
//    world *= Matrix::CreateTranslation(m_position);
//
//    // 生存していたら
//    if (m_isAlive == true)
//    {
//        // モデル表示
//        m_model->Draw(context, *states, world, view, proj); // モデルを描画する
//    }
//    // 生存していたら
//    if (m_isAlive == true)
//    {
//        // HPUIを描画する
//        m_hpUI->Render(context, view, proj);
//    }