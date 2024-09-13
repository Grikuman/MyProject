/*
    ファイル: IEnemyState.h
    クラス  : 敵ステートのインターフェース
*/

#pragma once

#include <DirectXMath.h>
#include <SimpleMath.h>

class IEnemyState
{
public:
    virtual ~IEnemyState() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Finalize() = 0;
};
