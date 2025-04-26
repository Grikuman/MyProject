/*
    ファイル名：NeedleBoss.h
    　　　概要：トゲボスの情報を管理するクラス
*/
#pragma once
#include <memory>
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/Interface/IEnemyState.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"
#include "Game/UI/EnemyUI/BossHPUI.h"
#include "Game/Effect/SmokeEffect.h"

#include "NeedleBossSearch.h"
#include "NeedleBossAttack.h"
#include "NeedleBossDown.h"

class Player;

class NeedleBoss : public IEnemy
{
public:
    // 位置を設定する
    void SetPosition(const DirectX::SimpleMath::Vector3 position)  { m_position = position; }
    // 速度を設定する
    void SetVelocity(const DirectX::SimpleMath::Vector3 velocity)  { m_velocity = velocity; }
    // 速度を加算する
    void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
    // 速度に係数をかける
    void ApplyVelocity(float scale)                                { m_velocity *= scale; }
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
    // ノックバックさせる
    void Knockback() override {  }
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
    // ノックバックしているか
    bool IsKnockback() const override { return true; }
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const override;
    // バウンディングボックスを取得する
    DirectX::BoundingBox GetBoundingBox() const override;

public:
    // プレイヤーを取得する
    Player* GetPlayer()                                            { return m_player; }
    // トゲボスサーチを取得する
    NeedleBossSearch* GetNeedleBossSearch()                            { return m_needleBossSearch.get(); }
    // トゲボスアタックを取得する
    NeedleBossAttack* GetNeedleBossAttack()                            { return m_needleBossAttack.get(); }
    // トゲボスダウンを取得する
    NeedleBossDown* GetNeedleBossDown()                                { return m_needleBossDown.get(); }
    
public:
    // コンストラクタ
    NeedleBoss(Player* player);
    // デストラクタ
    ~NeedleBoss() override;
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
    const float MAXHP = 300;

private:
    // プレイヤー
    Player* m_player;
    // ステート
    IEnemyState* m_currentState;
    // モデル
    DirectX::Model* m_model;
    // サーチ状態
    std::unique_ptr<NeedleBossSearch> m_needleBossSearch;
    // アタック状態
    std::unique_ptr<NeedleBossAttack> m_needleBossAttack;
    // ダウン状態
    std::unique_ptr<NeedleBossDown> m_needleBossDown;
    // 体力のUI
    std::unique_ptr<BossHPUI> m_bossHPUI;
    // 煙エフェクト
    std::unique_ptr<SmokeEffect> m_smokeEffect;
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

