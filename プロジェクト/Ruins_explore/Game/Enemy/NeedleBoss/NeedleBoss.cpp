/*
    ファイル名：NeedleBoss.cpp
    　　　概要：トゲボスの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "NeedleBoss.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include <cassert>
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
NeedleBoss::NeedleBoss(Player* player)
    :
    m_player{player},
    m_model{},
    m_needleBossSearch{},
    m_needleBossAttack{},
    m_needleBossDown{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
NeedleBoss::~NeedleBoss()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void NeedleBoss::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // コンテキストを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // デバイスを取得する
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // 位置を設定する
    m_position = position;

    // モデルを読み込む
    m_model = Resources::GetInstance()->GetModel(L"NeedleBoss");

    //* ステートを作成する *
    // サーチ状態
    m_needleBossSearch = std::make_unique<NeedleBossSearch>(this);
    m_needleBossSearch->Initialize();
    // アタック状態
    m_needleBossAttack = std::make_unique<NeedleBossAttack>(this);
    m_needleBossAttack->Initialize();
    // ダウン状態
    m_needleBossDown = std::make_unique<NeedleBossDown>(this);
    m_needleBossDown->Initialize();

    // ステートを設定する
    m_currentState = m_needleBossSearch.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void NeedleBoss::Update()
{
    m_isHit = false; 

    //生存しているか確認する
    CheckAlive(); 

    //現在のステートを更新する
    m_currentState->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void NeedleBoss::Render()
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

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void NeedleBoss::Finalize()
{
    
}

//---------------------------------------------------------
// バウンディングスフィアを取得する
//---------------------------------------------------------
DirectX::BoundingSphere NeedleBoss::GetBoundingSphere() const
{
    DirectX::SimpleMath::Vector3 center = m_position;
    float radius = 3.f;
    return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// ダメージを与える
//---------------------------------------------------------
void NeedleBoss::Damage(const float damage)
{
    m_hp -= damage;
}

//---------------------------------------------------------
// 生存しているか判定する
//---------------------------------------------------------
void NeedleBoss::CheckAlive()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}
