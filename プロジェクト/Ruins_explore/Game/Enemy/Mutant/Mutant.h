/*
    ファイル名：Mutant.h
    　　　概要：ミュータントの情報を管理するクラス
*/
#pragma once
#include "Game/Enemy/Mutant/States/MutantWalking.h"
#include "Game/Enemy/Mutant/States/MutantSlashing.h"
#include "Game/Enemy/Mutant/States/MutantRushing.h"
#include "Game/Interface/IEnemyState.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"

// 前方宣言
class Player;

class Mutant : public IEnemy
{
public:
    // 位置を設定する
    void SetPosition(const DirectX::SimpleMath::Vector3 position) { m_position = position; }
    // 速度を設定する
    void SetVelocity(const DirectX::SimpleMath::Vector3 velocity) { m_velocity = velocity; }
    // 速度を加算する
    void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
    // 速度に係数をかける
    void ApplyVelocity(float scale) { m_velocity *= scale; }
    // 回転速度を加算する
    void AddAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle *= angle; }
    // 角度を設定する
    void SetAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle = angle; }
    // 体力を設定する
    void SetHP(const float hp) { m_hp = hp; }
    // ダメージを受けているか設定する
    void SetHit(const bool isHit) { m_isHit = isHit; }
    // 生存状況を設定する
    void SetAlive(const bool isAlive) { m_isAlive = isAlive; }
    // ダメージを与える
    void Damage(const float damage) override { m_hp -= damage; }
    // ステートを変更する
    void ChangeState(IEnemyState* newState) { m_currentState = newState; }
public:
    // 位置を取得する
    DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
    // 速度を取得する
    DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
    // 角度を取得する
    DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }
    // 体力を取得する
    float GetHP() const { return m_hp; }
    // 最大体力を取得する
    float GetMAXHP() const { return MAXHP; }
    // ダメージを受けているか取得する
    bool GetHit() const { return m_isHit; }
    // 生存状況を取得する
    bool IsAlive() const override { return m_isAlive; }
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const override { return DirectX::BoundingSphere(m_position, COLLISION_SPHERE_SIZE); }
    // バウンディングボックスを取得する
    DirectX::BoundingBox GetBoundingBox() const override { return DirectX::BoundingBox(m_position, COLLISION_BOX_SIZE); }

public:
    // プレイヤーを取得する
    Player* GetPlayer() { return m_player; }
    // 歩き状態を取得する
    MutantWalking* GetMutantWalking() { return m_mutantWalking.get(); }
    // 突進状態を取得する
    MutantRushing* GetMutantRushing() { return m_mutantRushing.get(); }
    // 斬りつけ状態を取得する
    MutantSlashing* GetMutantSlashing() { return m_mutantSlashing.get(); }
    
public:
    // コンストラクタ
    Mutant(Player* player);
    // デストラクタ
    ~Mutant() override;
    // 初期化する
    void Initialize(DirectX::SimpleMath::Vector3 position) override;
    // 更新する
    void Update() override;
    // 描画する
    void Render() override;
    // 後処理をする
    void Finalize() override;

private:
    // 生存しているか判定する
    void CheckAlive();
    // プレイヤーの視点を自身に向ける
    void SetPlayerAngle();

private:
    // 最大体力
    const float MAXHP = 200;
    // 当たり判定(球)のサイズ
    const float COLLISION_SPHERE_SIZE = 2.0f;
    // 当たり判定(箱)のサイズ
    const DirectX::SimpleMath::Vector3 COLLISION_BOX_SIZE = { 1.0f,1.0f,1.0f };

private:
    // プレイヤー
    Player* m_player;
    // 現在の状態
    IEnemyState* m_currentState;
    // 歩き状態
    std::unique_ptr<MutantWalking> m_mutantWalking;
    // 突進状態
    std::unique_ptr<MutantRushing> m_mutantRushing;
    // 斬りつけ状態
    std::unique_ptr<MutantSlashing> m_mutantSlashing;
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

