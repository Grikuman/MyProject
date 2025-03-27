/*
    ファイル名：PracticeEnemy.cpp
    　　　概要：つのまるの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "PracticeEnemy.h"
#include "Game/Player/Player.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PracticeEnemy::PracticeEnemy(Player* player)
    : 
    m_player{player},
    m_model{},
    m_model_Hit{},
    m_position{},
    m_isHit{false},
    m_hitCnt{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PracticeEnemy::~PracticeEnemy()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PracticeEnemy::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // 位置を設定する
    m_position = position;
    // 攻撃を受けた回数を初期化
    m_hitCnt = 0;
    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"PracticeModel");
    m_model_Hit = Resources::GetInstance()->GetModel(L"PracticeModel_Hit");
    // モデルのエフェクト設定
    m_model->UpdateEffects([](DirectX::IEffect* effect)
        {
            auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
            if (lights)
            {
                lights->SetLightEnabled(0, false);
                lights->SetLightEnabled(1, false);
                lights->SetLightEnabled(2, false);
                lights->SetAmbientLightColor(DirectX::Colors::Black);
            }

            auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
            if (basicEffect)
            {
                basicEffect->SetEmissiveColor(DirectX::Colors::White);
            }
        });
    // モデルのエフェクト設定
    m_model_Hit->UpdateEffects([](DirectX::IEffect* effect)
        {
            auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
            if (lights)
            {
                lights->SetLightEnabled(0, false);
                lights->SetLightEnabled(1, false);
                lights->SetLightEnabled(2, false);
                lights->SetAmbientLightColor(DirectX::Colors::Black);
            }

            auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
            if (basicEffect)
            {
                basicEffect->SetEmissiveColor(DirectX::Colors::White);
            }
        });
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PracticeEnemy::Update()
{
    m_isHit = false; 
    // プレイヤーの視点を自身に向ける
    SetPlayerAngle();
    // 攻撃を受けているか判定
    CheckHit();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PracticeEnemy::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // コンテキスト・ステートを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(); 
    auto states = Graphics::GetInstance()->GetCommonStates(); 

    // ビュー・プロジェクションを取得する
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix(); 
    proj = Graphics::GetInstance()->GetProjectionMatrix(); 

    Matrix worldMatrix = 
        // スケール行列を作成
        Matrix::CreateScale(1.f) * 
        // 180度回転させる(モデルの向き調整)
        Matrix::CreateRotationY(DirectX::XM_PI) *
        // 移動行列を作成
        Matrix::CreateTranslation(m_position);
    // モデル表示
    if (m_isHit)
    {
        m_model_Hit->Draw(context, *states, worldMatrix, view, proj); // モデルを描画する
    }
    else
    {
        m_model->Draw(context, *states, worldMatrix, view, proj); // モデルを描画する
    }
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PracticeEnemy::Finalize()
{
    
}

//---------------------------------------------------------
// プレイヤーの視点を自身に向ける
//---------------------------------------------------------
void PracticeEnemy::SetPlayerAngle()
{
    // プレイヤーと敵の位置を取得
    DirectX::SimpleMath::Vector3 playerPosition = m_player->GetPosition();
    DirectX::SimpleMath::Vector3 enemyPosition = m_position;

    // プレイヤーと敵の方向ベクトルを計算
    DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;
    direction.y = 0.0f;  // 高さ方向を無視してY軸回りの回転だけを考慮

    // ベクトルの正規化
    direction.DirectX::SimpleMath::Vector3::Normalize();

    // プレイヤーが向くべき角度を計算
    float angle = atan2(direction.x, direction.z);  // X,Z平面での角度を計算

    // プレイヤーの向きを変更
    DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle, 0.0f, 0.0f);
    m_player->SetAngle(rotation);  // プレイヤーの回転を設定
}

//---------------------------------------------------------
// 攻撃を受けているか判定
//---------------------------------------------------------
void PracticeEnemy::CheckHit()
{
    // プレイヤーが攻撃している場合
    if (m_player->IsAttack())
    {
        // プレイヤー攻撃が当たっていたら
        if (m_player->GetPlayerAttackingNormal()->GetAttackRange().Intersects(GetBoundingSphere()))
        {
            if (!m_isHit)
            {
                m_isHit = true;
                m_hitCnt++;
            }
        }
    }
}

//---------------------------------------------------------
// バウンディングスフィアを取得する
//---------------------------------------------------------
DirectX::BoundingSphere PracticeEnemy::GetBoundingSphere()
{
    DirectX::SimpleMath::Vector3 center = m_position; // 当たり判定球の中心
    float radius = 1.0f;         // サイズに応じて調整
    return DirectX::BoundingSphere(center, radius);
}

