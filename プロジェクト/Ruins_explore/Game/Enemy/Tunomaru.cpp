/*
    ファイル名：Tunomaru.cpp
    　　　概要：つのまるの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Collision.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tunomaru::Tunomaru(Player* player)
    : 
    m_player{player},
    m_model{},
    m_ball{},
    m_tunomaruSearch{},
    m_tunomaruAttack{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
}

Tunomaru::~Tunomaru() {}

void Tunomaru::Initialize(Vector3 position)
{
    // コンテキストを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // D3Dデバイスを取得する
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // ボールを読み込む
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // 位置を設定する
    m_position = position;

    m_model = Resources::GetInstance()->GetModel(L"Tunomaru");

    // ライトを切る設定
    m_model->UpdateEffects([](DirectX::IEffect* effect)
    {
        // ライトをきる
        auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
        if (lights)
        {
            lights->SetLightEnabled(0, false);
            lights->SetLightEnabled(1, false);
            lights->SetLightEnabled(2, false);
            // 環境光を黒に
            lights->SetAmbientLightColor(DirectX::Colors::Black);
        }
        // 自己発光させる
        auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
        if (basicEffect)
        {
            basicEffect->SetEmissiveColor(DirectX::Colors::White);
        }
    });

    //HPUIを作成する
    m_hpUI = std::make_unique<HPUI>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice());
    m_hpUI->SetScale(1.f);
    m_hpUI->SetPosition(m_position);

    //* ステートを作成する *
    // サーチ状態
    m_tunomaruSearch = std::make_unique<TunomaruSearch>(this);
    m_tunomaruSearch->Initialize();
    // アタック状態
    m_tunomaruAttack = std::make_unique<TunomaruAttack>(this);
    m_tunomaruAttack->Initialize();
    // ダウン状態
    m_tunomaruDown = std::make_unique<TunomaruDown>(this);
    m_tunomaruDown->Initialize();

    // ステートを設定する
    m_currentState = m_tunomaruSearch.get();
}

void Tunomaru::Update()
{
    m_isHit = false; 

    //生存しているか確認する
    CheckAlive(); 

    //現在のステートを更新する
    m_currentState->Update();

    // HPUIを動かす
    m_hpUI->SetPosition(DirectX::SimpleMath::Vector3(m_position.x, m_position.y + 1.6f, m_position.z));
    // HPUIのHP情報を更新
    m_hpUI->SetHP(m_hp, MAXHP);

    // プレイヤーとの当たり判定
    Collision::GetInstance()->CheckHitPlayerToEnemy(this);
    Collision::GetInstance()->CheckPushBack(this);
}

void Tunomaru::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    // リソースを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    // ワールド行列
    Matrix world = Matrix::CreateScale(1.f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_angle));
    world *= Matrix::CreateTranslation(m_position);

    // 生存していたら
    if (m_isAlive == true)
    {
        // モデル表示
        m_model->Draw(context, *states, world, view, proj); // モデルを描画する
    }
    // 生存していたら
    if (m_isAlive == true)
    {
        // HPUIを描画する
        m_hpUI->Render(context, view, proj);
    }
}

void Tunomaru::Finalize()
{
    
}

// バウンディングスフィアを取得する
BoundingSphere Tunomaru::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 1.f;
    return BoundingSphere(center, radius);
}
// ダメージを与える
void Tunomaru::Damage(const float damage)
{
    m_hp -= damage;
}
// 生存しているか判定する
void Tunomaru::CheckAlive()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}

void Tunomaru::ChangeState(IEnemyState* newState)
{
    m_currentState = newState;
}
