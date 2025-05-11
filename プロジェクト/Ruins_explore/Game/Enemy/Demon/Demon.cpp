/*
    ファイル名：Demon.cpp
    　　　概要：ミュータントの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Demon.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Demon::Demon(Player* player)
    :
    m_player{player},
    m_currentState{},
    m_DemonWalking{},
    m_DemonPunching{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_hp{MAXHP},
    m_isHit(false),
    m_isAlive(true)
{
    // 歩き状態を作成する
    m_DemonWalking = std::make_unique<DemonWalking>(this);
    // 突進状態を作成する
    m_DemonPunching = std::make_unique<DemonPunching>(this);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Demon::~Demon()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Demon::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // 位置を設定する
    m_position = position;
    // 歩き状態を初期化する
    m_DemonWalking->Initialize();
    // 突進状態を初期化する
    m_DemonPunching->Initialize(); 
    // 初期の状態を設定する
    m_currentState = m_DemonWalking.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Demon::Update()
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
void Demon::Render()
{
    // 現在のステートを描画する
    m_currentState->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Demon::Finalize()
{
    
}

//---------------------------------------------------------
// 生存しているか判定する
//---------------------------------------------------------
void Demon::CheckAlive()
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
void Demon::SetPlayerAngle()
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
