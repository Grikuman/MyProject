/*
    ファイル名：RockBoss.h
    　　　概要：岩ボスの情報を管理するクラス
*/
#pragma once
#include <memory>
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/Interface/IEnemyState.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"

#include "RockBossSearch.h"
#include "RockBossAttack.h"
#include "RockBossDown.h"

class Player;

class RockBoss : public IEnemy
{
public:
    // 位置を設定する
    void SetPotision(const DirectX::SimpleMath::Vector3 position)  { m_position = position; }
    // 速度を設定する
    void SetVelocity(const DirectX::SimpleMath::Vector3 velocity)  { m_velocity = velocity; }
    // 速度を加算する
    void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
    // 速度に係数をかける
    void ApplyVelocity(float scale) { m_velocity *= scale; }
    // 回転速度を加算する
    void AddAngle(const DirectX::SimpleMath::Quaternion angle)     { m_angle *= angle; }
    // 角度を設定する
    void SetAngle(const DirectX::SimpleMath::Quaternion angle)     { m_angle = angle; }
    // 体力を設定する
    void SetHP(const float hp)                                     { m_hp = hp; }
    // ダメージを受けているか設定する
    void SetHit(const bool isHit)                                  { m_isHit = isHit; }
    // 生存状況を設定する
    void SetAlive(const bool isAlive)                              { m_isAlive = isAlive; }
    // ダメージを与える
    void Damage(const float damage) override;
    // ステートを変更する
    void ChangeState(IEnemyState* newState)                        { m_currentState = newState; }
public:
    // 位置を取得する
    DirectX::SimpleMath::Vector3 GetPosition() const override      { return m_position; }
    // 速度を取得する
    DirectX::SimpleMath::Vector3 GetVelocity() const               { return m_velocity; }
    // 角度を取得する
    DirectX::SimpleMath::Quaternion GetAngle() const               { return m_angle; }
    // 体力を取得する
    float GetHP() const                                            { return m_hp; }
    // 最大体力を取得する
    float GetMAXHP() const                                         { return MAXHP; }
    // ダメージを受けているか取得する
    bool GetHit() const                                            { return m_isHit; }
    // 生存状況を取得する
    bool IsAlive() const override                                  { return m_isAlive; }
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const override;

public:
    // プレイヤーを取得する
    Player* GetPlayer()                                            { return m_player; }

    // 岩ボスサーチを取得する
    RockBossSearch* GetRockBossSearch()                            { return m_RockBossSearch.get(); }
    // 岩ボスアタックを取得する
    RockBossAttack* GetRockBossAttack()                            { return m_RockBossAttack.get(); }
    // 岩ボスダウンを取得する
    RockBossDown* GetRockBossDown()                                { return m_RockBossDown.get(); }
    
public:
    // コンストラクタ
    RockBoss(Player* player);
    // デストラクタ
    ~RockBoss();
    // 初期化する
    void Initialize(DirectX::SimpleMath::Vector3 position);
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理をする
    void Finalize();

private:
    // 生存しているか判定する
    void CheckAlive();

private:
    // 最大体力
    const float MAXHP = 100;

private:
    // プレイヤー
    Player* m_player;
    // ステート
    IEnemyState* m_currentState;
    // モデル
    DirectX::Model* m_model;
    // モデル
    std::unique_ptr<DirectX::GeometricPrimitive> m_ball;

    // サーチ状態
    std::unique_ptr<RockBossSearch> m_RockBossSearch;
    // アタック状態
    std::unique_ptr<RockBossAttack> m_RockBossAttack;
    // ダウン状態
    std::unique_ptr<RockBossDown> m_RockBossDown;

    // 位置
    DirectX::SimpleMath::Vector3 m_position;
    // 速度
    DirectX::SimpleMath::Vector3 m_velocity;
    // 角度
    DirectX::SimpleMath::Quaternion m_angle;
    // 体力
    float m_hp;
    // ダメージを受けているか
    bool m_isHit;
    // 生存状況
    bool m_isAlive;
};

