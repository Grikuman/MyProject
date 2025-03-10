/*
    ファイル名：InvincibleEffect.h
    　　　概要：プレイヤーの無敵エフェクトを管理するクラス
*/
#pragma once
class Player;

class InvincibleEffect
{
public:
    InvincibleEffect(Player* player);
    ~InvincibleEffect();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();
private:
    // エフェクトの大きさ
    const float SIZE = 3.6f;

private:
    // プレイヤー
    Player* m_player;
    // 球
    std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
    // ブレンドステート
    ID3D11BlendState* m_blendState;
    // アルファ値
    float m_alpha;
};


