#pragma once

#include <memory>
#include "IEnemy.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/UI/HPUI.h"

class CommonResources;

class Tunomaru
{
public:
    // コンストラクタ
    Tunomaru();
    // デストラクタ
    ~Tunomaru();
    // 初期化する
    void Initialize(
        CommonResources* resources, 
        DirectX::SimpleMath::Vector3 position);
    // 更新する
    void Update();
    // 描画する
    void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
    // 後処理をする
    void Finalize();
public:


public:
    // 位置を設定する
    void SetPotision(const DirectX::SimpleMath::Vector3 position) { m_position = position; }
    // 体力を設定する
    void SetHP(const float hp) { m_hp = hp; }
    // ダメージを受けているか設定する
    void SetHit(const bool isHit) { m_isHit = isHit; }
    // 生存状況を設定する
    void SetAlive(const bool isAlive) { m_isAlive = isAlive; }
public:
    // 位置を取得する
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
    // 体力を取得する
    float GetHP() const { return m_hp; }
    // ダメージを受けているか取得する
    bool GetHit() const { return m_isHit; }
    // 生存状況を取得する
    bool GetIsAlive() const { return m_isAlive; }

    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const;
private:
    // 生存しているか判定する
    void IsDead();
private:
    //HPUI
    std::unique_ptr<HPUI> m_hpUI;
    // 共有リソース
    CommonResources* m_commonResources;
    // モデル
    std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;

    // 位置
    DirectX::SimpleMath::Vector3 m_position;
    // 体力
    float m_hp;
    // 最大体力
    const float MAXHP = 100;
    // ダメージを受けているか
    bool m_isHit;
    // 生存状況
    bool m_isAlive;
};

