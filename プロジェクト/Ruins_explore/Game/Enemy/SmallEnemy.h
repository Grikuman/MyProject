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

class SmallEnemy : public IEnemy
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
    SmallEnemy();
    ~SmallEnemy();

    void Initialize(
        CommonResources* resources, 
        NRLib::TPS_Camera* camera, 
        DirectX::SimpleMath::Vector3 position) override;
    void Update() override;
    void Render() override;
    void Finalize() override;

    void SetState(int state) override;
    int GetState() const override;

    void Hit(float damage) override;

    DirectX::BoundingSphere GetBoundingSphere() const override;
};

