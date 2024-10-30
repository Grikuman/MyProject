/*
    ファイル: RockBoss.cpp
    クラス  : 岩ボスクラス
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

using namespace DirectX;
using namespace DirectX::SimpleMath;

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

void RockBoss::Initialize(Vector3 position)
{
    // コンテキストを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // D3Dデバイスを取得する
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // ボールを読み込む
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // 位置を設定する
    m_position = position;

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
    if (m_isAlive)
    {
        //現在のステートを更新する
        m_currentState->Update();
    }

    // プレイヤーとの当たり判定
    Collision::GetInstance()->CheckHitRockBoss(this);
}

void RockBoss::Render()
{
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto view = Graphics::GetInstance()->GetViewMatrix();
    auto proj = Graphics::GetInstance()->GetProjectionMatrix();
    // 現在のステートを描画する
    m_currentState->Render();
}

void RockBoss::Finalize()
{
    
}

// バウンディングスフィアを取得する
BoundingSphere RockBoss::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 3.f;
    return BoundingSphere(center, radius);
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
