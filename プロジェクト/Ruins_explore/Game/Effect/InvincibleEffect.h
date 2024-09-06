#pragma once
class CommonResources;
class Player;

class InvincibleEffect
{
public:
    InvincibleEffect(Player* player);
    ~InvincibleEffect();
    // 初期化する
    void Initialize(CommonResources* resources);
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();
private:
    // 共通のステート
    CommonResources* m_commonResources;
    // プレイヤー
    Player* m_player;
    // 球
    std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
    // ブレンドステート
    ID3D11BlendState* m_blendState;

    // アルファ値
    float m_alpha;
};


