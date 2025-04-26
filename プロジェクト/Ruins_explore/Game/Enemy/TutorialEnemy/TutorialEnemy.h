/*
    ファイル名：TutorialEnemy.h
    　　　概要：チュートリアルの敵の情報を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Interface/ICollisionObject.h"

class Player;

class TutorialEnemy : public IEnemy
{
public:
    // 生存状況を取得する
    bool IsAlive() const override { return true; }
    // バウンディングボックスを取得する
    DirectX::BoundingBox GetBoundingBox() const override 
    { 
        // 当たり判定ボックスの中心を設定
        DirectX::SimpleMath::Vector3 center = DirectX::SimpleMath::Vector3(0,0,0);
        // ボックスの大きさ（半径）を設定
        DirectX::SimpleMath::Vector3 extents(1.0f, 1.0f, 1.0f);
        return DirectX::BoundingBox(center, extents);
    }

public:
    // 位置を取得する
    DirectX::SimpleMath::Vector3 GetPosition() const override 
    { 
        return DirectX::SimpleMath::Vector3(0, 0, 0);
    };
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const override 
    {
        DirectX::SimpleMath::Vector3 center = DirectX::SimpleMath::Vector3(0,0,0);
        float radius = 2.f;
        return DirectX::BoundingSphere(center, radius);
    };
public:
    // 位置を設定する
    void SetPosition(const DirectX::SimpleMath::Vector3 position) override {};
    // ダメージを与える
    void Damage(const float damage) override {};

public:
    // コンストラクタ
    TutorialEnemy(Player* player) {};
    // デストラクタ
    ~TutorialEnemy() override {};
    // 初期化する
    void Initialize(DirectX::SimpleMath::Vector3 position) override {};
    // 更新する
    void Update() override {};
    // 描画する
    void Render() override {};
    // 後処理をする
    void Finalize() override {};
};

