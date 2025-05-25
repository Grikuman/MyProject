/*
    ファイル名：Mutant.cpp
    　　　概要：ミュータントの情報を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Mutant.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Mutant::Mutant()
    :
    m_player{},
    m_currentState{},
    m_mutantWalking{},
    m_mutantRushing{},
    m_mutantSlashing{},
    m_position{},
    m_jumpPlayerPos{},
    m_velocity{},
    m_angle{},
    m_hp{MAXHP},
    m_isHit(false),
    m_isAlive(true)
{
    // 歩き状態を作成する
    m_mutantWalking = std::make_unique<MutantWalking>();
    // 突進状態を作成する
    m_mutantRushing = std::make_unique<MutantRushing>();
    // 斬りつけ状態を作成する
    m_mutantSlashing = std::make_unique<MutantSlashing>();
    // ジャンプ状態を作成する
    m_mutantJumping = std::make_unique<MutantJumping>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Mutant::~Mutant()
{

}

//---------------------------------------------------------
// イベントを登録する
//---------------------------------------------------------
void Mutant::RegisterEvent()
{
    // ミュータントのポインタを取得する
    EventMessenger::AttachGetter(GetterList::GetMutant, std::bind(&Mutant::GetMutant, this));
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Mutant::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // イベントを登録する
    RegisterEvent();
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // 位置を設定する
    m_position = position;
    // 歩き状態を初期化する
    m_mutantWalking->Initialize();
    // 突進状態を初期化する
    m_mutantRushing->Initialize(); 
    // 斬りつけ状態を初期化する
    m_mutantSlashing->Initialize(); 
    // ジャンプ状態を初期化する
    m_mutantJumping->Initialize();
    // 初期の状態を設定する
    m_currentState = m_mutantWalking.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Mutant::Update()
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
void Mutant::Render()
{
    // 現在のステートを描画する
    m_currentState->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Mutant::Finalize()
{
    
}

//---------------------------------------------------------
// 生存しているか判定する
//---------------------------------------------------------
void Mutant::CheckAlive()
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
void Mutant::SetPlayerAngle()
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
