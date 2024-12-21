/*
    ファイル名：ICollisionObject.h
    　　　概要：当たり判定のある物体のインターフェース
*/

#pragma once
#include "pch.h"

class ICollisionObject
{
public:
    virtual ~ICollisionObject() = default;

    // バウンディングスフィアを取得する
    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;

    // ダメージを与える
    virtual void Damage(const float damage) = 0;
};
