/*
    ファイル名：Warrok.cpp
    　　　概要：ミュータントの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Warrok.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Warrok::Warrok(Player* player)
    :
    m_player{player},
    m_currentState{},
    m_WarrokWalking{},
    m_WarrokPunching{},
    m_WarrokKicking{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_hp{MAXHP},
    m_isHit(false),
    m_isAlive(true)
{
    // 歩き状態を作成する
    m_WarrokWalking = std::make_unique<WarrokWalking>(this);
    // 突進状態を作成する
    m_WarrokPunching = std::make_unique<WarrokPunching>(this);
    // 斬りつけ状態を作成する
    m_WarrokKicking = std::make_unique<WarrokKicking>(this);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Warrok::~Warrok()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Warrok::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // 位置を設定する
    m_position = position;
    // 歩き状態を初期化する
    m_WarrokWalking->Initialize();
    // 突進状態を初期化する
    m_WarrokPunching->Initialize(); 
    // 斬りつけ状態を初期化する
    m_WarrokKicking->Initialize(); 
    // 初期の状態を設定する
    m_currentState = m_WarrokWalking.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Warrok::Update()
{
    // ダメージ判定を無しにする
    m_isHit = false; 
    // 速度をリセットする
    m_velocity = DirectX::SimpleMath::Vector3::Zero;

    //生存しているか確認する
    CheckAlive();
    //現在のステートを更新する
    m_currentState->Update();
    // プレイヤーの視点を自身に向ける
    SetPlayerAngle();
    // プレイヤーとの当たり判定を行う
    Collision::GetInstance()->BossEnemy(this);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Warrok::Render()
{
    // 現在のステートを描画する
    m_currentState->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Warrok::Finalize()
{
    
}

//---------------------------------------------------------
// 生存しているか判定する
//---------------------------------------------------------
void Warrok::CheckAlive()
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
void Warrok::SetPlayerAngle()
{
    // プレイヤーと敵の位置を取得
    DirectX::SimpleMath::Vector3 playerPosition = m_player->GetPosition();
    DirectX::SimpleMath::Vector3 enemyPosition = m_position;
    // プレイヤーと敵の方向ベクトルを計算
    DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;
    // 高さ方向を無視してY軸回りの回転だけを考慮する
    direction.y = 0.0f;
    // ベクトルの正規化
    direction.DirectX::SimpleMath::Vector3::Normalize();
    // プレイヤーが向くべき角度を計算
    float angle = atan2(direction.x, direction.z);  // X,Z平面での角度を計算

    // プレイヤーの向きを変更
    DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle, 0.0f, 0.0f);
    m_player->SetAngle(rotation);  // プレイヤーの回転を設定
}
