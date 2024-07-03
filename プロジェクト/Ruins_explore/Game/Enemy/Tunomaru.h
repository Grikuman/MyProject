#pragma once

#include <memory>
#include "IEnemy.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>

class CommonResources;
namespace NRLib
{
    class TPS_Camera;
}

class Tunomaru : public IEnemy
{
public:
    enum STATE
    {
        ALIVE,
        DEAD,
    };

private:
    // 共有リソース
    CommonResources* m_commonResources;
    // カメラ
    NRLib::TPS_Camera* m_camera;
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
    // ヒットポイント
    float m_hp;

public:
    Tunomaru();
    ~Tunomaru();

    void Initialize(
        CommonResources* resources, 
        NRLib::TPS_Camera* camera, 
        DirectX::SimpleMath::Vector3 position) override;
    void Update() override;
    void Render() override;
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

