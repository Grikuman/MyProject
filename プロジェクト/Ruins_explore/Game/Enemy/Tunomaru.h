#pragma once

#include <memory>
#include "IEnemy.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/UI/HPUI.h"

class CommonResources;

class Tunomaru : public IEnemy
{
public:
    enum STATE
    {
        ALIVE,
        DEAD,
    };

private:
    //HPUI
    std::unique_ptr<HPUI> m_hpUI;
    // 共有リソース
    CommonResources* m_commonResources;
    // モデル
    std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;
    // 座標
    DirectX::SimpleMath::Vector3 m_position;
    // バウンディングスフィア
    DirectX::BoundingSphere m_boundingSphere;
    // ステート
    STATE m_state;
    // 当たったかどうか
    bool m_isHit;
    // HP
    float m_hp;
    //最大HP
    const float MAXHP = 100;

public:
    Tunomaru();
    ~Tunomaru();

    void Initialize(
        CommonResources* resources, 
        DirectX::SimpleMath::Vector3 position) override;
    void Update() override;
    void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) override;
    void Finalize() override;

    // 状態を設定する
    void SetState(int state) override;
    // 状態を取得する
    int GetState() const override;
    // 攻撃を受けた際にHPを減らす
    void Hit(float damage) override;
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const override;
private:
    // 生存しているか判定する
    void IsDead();
};

