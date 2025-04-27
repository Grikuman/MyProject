/*
    ファイル名：Debris.cpp
    　　　概要：破片のエフェクトクラス
*/
#include "pch.h"
#include "DebrisEffect.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
DebrisEffect::DebrisEffect()
    : 
    m_spawnTimer(0.0f)
{
    std::srand(static_cast<unsigned int>(std::time(0)));  // 乱数の初期化
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
DebrisEffect::~DebrisEffect()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void DebrisEffect::Initialize()
{
    m_particles.clear();

    // コンテキストを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // 岩のプリミティブを作成する
    m_rockPrimitive = DirectX::GeometricPrimitive::CreateCube(context, 0.1f);  // 立方体
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void DebrisEffect::Update(const DirectX::SimpleMath::Vector3& spawnPosition)
{
    // パーティクルの更新
    for (auto& particle : m_particles)
    {
        // 位置を速度に基づいて更新
        particle.position.x += particle.velocity.x;
        particle.position.y += particle.velocity.y;
        particle.position.z += particle.velocity.z;

        // 寿命を減らす
        particle.lifetime -= 0.016f;  // 1フレームあたり0.016秒と仮定

        // 寿命が尽きたら削除
        if (particle.lifetime <= 0.0f)
        {
            particle = m_particles.back();
            m_particles.pop_back();
        }
    }
    // 新しいパーティクルを発生させる
    m_spawnTimer += 0.016f;
    if (m_spawnTimer >= SPAWN_RATE)
    {
        SpawnParticle(spawnPosition);  // 引数で渡された位置を使用
        m_spawnTimer = 0.0f;
    }
}

//---------------------------------------------------------
// パーティクルを生成する
//---------------------------------------------------------
void DebrisEffect::SpawnParticle(const DirectX::SimpleMath::Vector3& position)
{
    if (m_particles.size() < MAX_PARTICLE)
    {
        Particle newParticle;
        newParticle.position = position;
        newParticle.position.y -= 0.8f;

        // ランダムな速度を設定
        newParticle.velocity = DirectX::SimpleMath::Vector3
        (
            (std::rand() % 4 - 2) * 0.01f,  // x方向のランダム速度（-2 から 2 の範囲）
            (std::rand() % 2) * -0.01f,     // y方向のランダム速度（負の範囲）
            (std::rand() % 4 - 2) * 0.01f   // z方向のランダム速度（-2 から 2 の範囲）
        );
        // パーティクルの寿命を設定する
        newParticle.lifetime = PARTICLE_LIFETIME;

        m_particles.push_back(newParticle);
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void DebrisEffect::Render()
{
    // ビュー行列を取得する
    auto view = Graphics::GetInstance()->GetViewMatrix();
    // プロジェクション行列を取得する
    auto proj = Graphics::GetInstance()->GetProjectionMatrix();

    // 破片の描画処理
    for (const auto& particle : m_particles)
    {
        // パーティクルの位置に基づいて岩を描画
        DirectX::SimpleMath::Matrix worldMatrix = DirectX::SimpleMath::Matrix::CreateTranslation(particle.position);
        // ここで岩のジオメトリを描画
        m_rockPrimitive->Draw(worldMatrix, view,proj,DirectX::Colors::SandyBrown);
    }
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void DebrisEffect::Finalize()
{
    m_particles.clear();
}
