/*
    ファイル名：ICollisionObject.h
    　　　概要：当たり判定のある物体のインターフェース
*/

#pragma once
#include "pch.h"

class ICollisionObject
{
public:
    // 位置を設定する
    virtual void SetPotision(const DirectX::SimpleMath::Vector3 position) = 0;

public:
    // 位置を取得する
    virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
    // バウンディングスフィアを取得する
    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;

    // ダメージを与える
    virtual void Damage(const float damage) = 0;
    virtual ~ICollisionObject() = default;
};
