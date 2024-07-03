//*=======================================================*
// IEnemy.h
// エネミーのインターフェースクラス
// 
//*=======================================================*

#pragma once

#include <DirectXMath.h>
#include <SimpleMath.h>
#include "Game/CommonResources.h"
#include "Libraries/NRLib/TPS_Camera.h"

class IEnemy
{
public:
    virtual ~IEnemy() = default;

    virtual void Initialize(
        class CommonResources* resources, 
        class NRLib::TPS_Camera* camera, 
        DirectX::SimpleMath::Vector3 position) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Finalize() = 0;

    // 状態を設定する
    virtual void SetState(int state) = 0;
    // 状態を取得する
    virtual int GetState() const = 0;
    // 攻撃を受けた際にHPを減らす
    virtual void Hit(float damage) = 0;
    // バウンディングスフィアを取得する
    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;
private:
    // 生存しているか判定する
    virtual void IsDead() = 0;
};
