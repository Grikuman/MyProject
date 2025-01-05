/*
    ファイル名：RockBoss.cpp
    　　　概要：岩ボスの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "RockBoss.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "WorkTool/Collision.h"
#include "WorkTool/Resources.h"

RockBoss::RockBoss(Player* player)
    :
    m_player{player},
    m_model{},
    m_ball{},
    m_RockBossSearch{},
    m_RockBossAttack{},
    m_RockBossDown{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
}

RockBoss::~RockBoss() {}

void RockBoss::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // コンテキストを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // D3Dデバイスを取得する
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // ボールを読み込む
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // 位置を設定する
    m_position = position;

    // モデルを読み込む
    m_model = Resources::GetInstance()->GetModel(L"RockBoss");

    // ライトを切る設定
    //m_model->UpdateEffects([](DirectX::IEffect* effect)
    //{
    //    // ライトをきる
    //    auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
    //    if (lights)
    //    {
    //        lights->SetLightEnabled(0, false);
    //        lights->SetLightEnabled(1, false);
    //        lights->SetLightEnabled(2, false);
    //        // 環境光を黒に
    //        lights->SetAmbientLightColor(DirectX::Colors::Black);
    //    }
    //    // 自己発光させる
    //    auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
    //    if (basicEffect)
    //    {
    //        basicEffect->SetEmissiveColor(DirectX::Colors::White);
    //    }
    //});

    //* ステートを作成する *
    // サーチ状態
    m_RockBossSearch = std::make_unique<RockBossSearch>(this);
    m_RockBossSearch->Initialize();
    // アタック状態
    m_RockBossAttack = std::make_unique<RockBossAttack>(this);
    m_RockBossAttack->Initialize();
    // ダウン状態
    m_RockBossDown = std::make_unique<RockBossDown>(this);
    m_RockBossDown->Initialize();

    // ステートを設定する
    m_currentState = m_RockBossSearch.get();
}

void RockBoss::Update()
{
    m_isHit = false; 

    //生存しているか確認する
    CheckAlive(); 

    //現在のステートを更新する
    m_currentState->Update();
}

void RockBoss::Render()
{
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
        Matrix::CreateScale(0.8f) *
        // 180度回転させる(モデルが逆を向いていたので)
        Matrix::CreateRotationY(DirectX::XM_PI) *
        // 回転行列を作成
        Matrix::CreateFromQuaternion(m_angle) *
        // 移動行列を作成
        Matrix::CreateTranslation(m_position);

    // モデル表示
    m_model->Draw(context, *states, worldMatrix, view, proj);
}

void RockBoss::Finalize()
{
    
}

// バウンディングスフィアを取得する
DirectX::BoundingSphere RockBoss::GetBoundingSphere() const
{
    DirectX::SimpleMath::Vector3 center = m_position;
    float radius = 3.f;
    return DirectX::BoundingSphere(center, radius);
}
// ダメージを与える
void RockBoss::Damage(const float damage)
{
    m_hp -= damage;
}
// 生存しているか判定する
void RockBoss::CheckAlive()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}
