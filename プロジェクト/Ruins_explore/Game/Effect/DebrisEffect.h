#pragma once

class DebrisEffect 
{

public:
    // 新しいパーティクルを発生させる
    void SpawnParticle(const DirectX::SimpleMath::Vector3& position);

public:
    // コンストラクタ
    DebrisEffect();
    // デストラクタ
    ~DebrisEffect();

    // 初期化する
    void Initialize();
    // 更新する
    void Update(const DirectX::SimpleMath::Vector3& spawnPosition);
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    // パーティクルの構造体
    struct Particle
    {
        DirectX::SimpleMath::Vector3 position;  // 位置
        DirectX::SimpleMath::Vector3 velocity;  // 速度
        float lifetime;              // 寿命
    };
private:
    // 最大パーティクル数
    const float MAX_PARTICLE = 50;
    // パーティクルのスポーン間隔
    const float SPAWN_RATE = 0.01f;
    // パーティクルの寿命
    const float PARTICLE_LIFETIME = 0.5f;

private:
    // パーティクルリスト
    std::vector<Particle> m_particles;
    // スポーンタイマー
    float m_spawnTimer;
    // 岩のプリミティブ
    std::shared_ptr<DirectX::GeometricPrimitive> m_rockPrimitive;
};
