/*
    ファイル名：InvincibleEffect.h
    　　　概要：プレイヤーの無敵エフェクトを管理するクラス
*/
#pragma once

class Player;

class InvincibleEffect
{
public:
    // コンストラクタ
    InvincibleEffect(Player* player);
    // デストラクタ
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
    // エフェクト球の大きさ
    const float SIZE = 3.8f;
    // エフェクト球のずらす量
    const DirectX::SimpleMath::Vector3 SHIFT_POS = { 0.0f,0.3f,0.0f };
    // アルファ値
    const float ALPHA = 0.3f;
    // アルファ値の減少速度
    const float ALPHA_DECREASE_SPEED = 0.03f;

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


