/*
    ファイル名：SwordEffect.h
    　　　概要：プレイヤーの斬撃エフェクトを管理するクラス
*/
#pragma once

class SwordEffect
{
public:
    // コンストラクタ
    SwordEffect();
    // デストラクタ
    ~SwordEffect();
    // 初期化する
    void Initialize(const DirectX::SimpleMath::Vector3& position);
    // 更新処理
    void Update(const DirectX::SimpleMath::Vector3& position);
    // 描画処理
    void Render();
    // 終了処理
    void Finalize();

private:
    // 共通のステート
    DirectX::CommonStates* m_commonStates;
    // 入力レイアウト
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    // テクスチャ用
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture[6];
    // プリミティブバッチ
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
    // エフェクト
    std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;

    // エフェクトの位置
    DirectX::SimpleMath::Vector3 m_position;
    // 画像変更カウント
    int m_cnt;
};

