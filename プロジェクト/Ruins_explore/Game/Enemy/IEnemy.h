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

    virtual void SetState(int state) = 0;
    virtual int GetState() const = 0;

    virtual void Hit(float damage) = 0;

    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;
};
