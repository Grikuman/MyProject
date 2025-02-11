/*
    ファイル名：SwordEffect.h
    　　　概要：プレイヤーの斬撃エフェクトを管理するクラス
*/
#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <DirectXMath.h>

class SwordEffect
{
public:
    // プレイヤーの位置を設定する
    void SetPosition(const DirectX::SimpleMath::Vector3& position);
public:
    // コンストラクタ
    SwordEffect(ID3D11Device* device);
    // デストラクタ
    ~SwordEffect();
    // 更新処理
    void Update();
    // 描画処理
    void Render(ID3D11DeviceContext1* context,DirectX::SimpleMath::Matrix view,DirectX::SimpleMath::Matrix proj);
    // 終了処理
    void Finalize();

private:
    // 共通のステート
    std::unique_ptr<DirectX::CommonStates> m_commonStates;
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

