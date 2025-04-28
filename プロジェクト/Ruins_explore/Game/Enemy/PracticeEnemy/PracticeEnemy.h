/*
    ファイル名：PracticeEnemy.h
    　　　概要：練習用の敵の情報を管理するクラス
*/
#pragma once

class Player;

class PracticeEnemy
{
public:
    // ダメージを受けているか設定する
    void SetHit(const bool isHit) { m_isHit = isHit; }

public:
    // 位置を取得する
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
    // 攻撃を受けた回数を取得する
    int GetHitCount() const { return m_hitCnt; }
    // 攻撃を受けているか取得する
    bool GetHit() const { return m_isHit; }
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() { return DirectX::BoundingSphere(m_position, COLLISION_SPHERE_SIZE); }

public:
    // コンストラクタ
    PracticeEnemy(Player* player);
    // デストラクタ
    ~PracticeEnemy();
    // 初期化する
    void Initialize(DirectX::SimpleMath::Vector3 position);
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理をする
    void Finalize();

private:
    // プレイヤーの視点を自身に向ける
    void SetPlayerAngle();
    // 攻撃を受けているか判定
    void CheckHit();

private:
    // 当たり判定(球)のサイズ
    const float COLLISION_SPHERE_SIZE = 1.0f;

private:
    // プレイヤー
    Player* m_player;
    // モデル
    DirectX::Model* m_model;
    DirectX::Model* m_model_Hit;
    // 位置
    DirectX::SimpleMath::Vector3 m_position;
    // 攻撃を受けているか
    bool m_isHit;
    // 攻撃を受けた回数
    int m_hitCnt;
};

