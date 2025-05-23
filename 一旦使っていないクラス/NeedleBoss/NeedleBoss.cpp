/*
    ファイル名：NeedleBoss.cpp
    　　　概要：トゲボスの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "NeedleBoss.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
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
    m_currentState{},
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
    //* ステートを作成する *
    // サーチ状態
    m_needleBossSearch = std::make_unique<NeedleBossSearch>(this);
    // アタック状態
    m_needleBossAttack = std::make_unique<NeedleBossAttack>(this);
    // ダウン状態
    m_needleBossDown = std::make_unique<NeedleBossDown>(this);
    // 体力のUIを作成する
    m_bossHPUI = std::make_unique<BossHPUI>();
    // 煙エフェクトを作成する
    m_smokeEffect = std::make_unique<SmokeEffect>();
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
    // 位置を設定する
    m_position = position;
    // モデルを読み込む
    m_model = Resources::GetInstance()->GetModel(L"NeedleBoss");

    //* ステートを初期化する *
    // サーチ状態
    m_needleBossSearch->Initialize();
    // アタック状態
    m_needleBossAttack->Initialize();
    // ダウン状態
    m_needleBossDown->Initialize();
    // 体力のUIを初期化する
    m_bossHPUI->Initialize(Graphics::GetInstance()->GetDeviceResources(),1920,720);

    // ステートを設定する
    m_currentState = m_needleBossSearch.get();
    // 煙エフェクトを初期化する
    m_smokeEffect->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void NeedleBoss::Update()
{
    m_isHit = false; 
    m_velocity = DirectX::SimpleMath::Vector3::Zero;

    //生存しているか確認する
    CheckAlive();
    //現在のステートを更新する
    m_currentState->Update();
    // プレイヤーの視点を自身に向ける
    SetPlayerAngle();
    // 体力UIを更新する
    m_bossHPUI->Update(m_hp, MAXHP);
    // プレイヤーとの当たり判定
    Collision::GetInstance()->BossEnemy(this);
    // 煙エフェクトを更新する
    m_smokeEffect->Update(m_position + DirectX::SimpleMath::Vector3(0.0f, -0.3f, 0.0f));
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
        Matrix::CreateScale(1.0f) *
        // 180度回転させる(モデルが逆を向いていたので)
        //Matrix::CreateRotationY(DirectX::XM_PI) *
        // 回転行列を作成
        Matrix::CreateFromQuaternion(m_angle) *
        // 移動行列を作成
        Matrix::CreateTranslation(m_position);

    if (m_currentState == m_needleBossDown.get())
    {
        worldMatrix =
            // スケール行列を作成
            Matrix::CreateScale(1.0f) *
            // 少し下を向かせる
            Matrix::CreateRotationX(DirectX::XMConvertToRadians(30.0f)) *
            // 回転行列を作成
            Matrix::CreateFromQuaternion(m_angle) *
            // 移動行列を作成
            Matrix::CreateTranslation(m_position);
    }

    // 煙エフェクト
    m_smokeEffect->CreateBillboard(m_player->GetPosition(), m_player->GetCamera()->GetEyePosition(), m_player->GetCamera()->GetUpVector());
    m_smokeEffect->Render(view, proj);
    // モデル表示
    m_model->Draw(context, *states, worldMatrix, view, proj);
    // 体力UIを描画する
    m_bossHPUI->Render();
    // 現在のステートを描画する
    m_currentState->Render();
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
    float radius = 2.f;
    return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// バウンディングボックスを取得する
//---------------------------------------------------------
DirectX::BoundingBox NeedleBoss::GetBoundingBox() const
{
    // 当たり判定ボックスの中心を設定
    DirectX::SimpleMath::Vector3 center = m_position;
    // ボックスの大きさ（半径）を設定
    DirectX::SimpleMath::Vector3 extents(1.0f, 1.0f, 1.0f); // サイズに応じて調整
    return DirectX::BoundingBox(center, extents);
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

//---------------------------------------------------------
// プレイヤーの視点を自身に向ける
//---------------------------------------------------------
void NeedleBoss::SetPlayerAngle()
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
