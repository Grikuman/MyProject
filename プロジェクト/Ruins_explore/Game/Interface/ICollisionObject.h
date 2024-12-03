/*
    ファイル: IEnemyState.h
    クラス  : 敵ステートのインターフェース
*/

#pragma once
#include "pch.h"

class ICollisionObject
{
public:
    virtual ~ICollisionObject() = default;

    // バウンディングスフィアを取得する
    virtual DirectX::BoundingSphere GetBoundingSphere() const
    {
        return m_boundingSphere;
    }

private:
    // バウンディングスフィア
    DirectX::BoundingSphere m_boundingSphere;
};
