/*
    ファイル: IEnemyState.h
    クラス  : 敵ステートのインターフェース
*/

#pragma once

#include <DirectXMath.h>
#include <SimpleMath.h>
#include "Game/CommonResources.h"
#include "Libraries/NRLib/TPS_Camera.h"

class IEnemyState
{
public:
    virtual ~IEnemyState() = default;

    virtual void Initialize(CommonResources* resources) = 0;
    virtual void Update() = 0;
    virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) = 0;
    virtual void Finalize() = 0;
};
