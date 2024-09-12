#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

class HPUI 
{
private:
    //HPの緑部分
    static const DirectX::VertexPositionColor VERTICES_GREEN[4];
    //HPの赤部分
    static const DirectX::VertexPositionColor VERTICES_RED[4];

    //  座標用の変数を作る
    DirectX::SimpleMath::Vector3 m_Position;

    //  サイズ用の変数
    float m_scale;

    // 入力レイアウト 
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

    //共通ステートオブジェクトへのポインタ
    std::unique_ptr<DirectX::CommonStates> m_States;

    // テクスチャハンドル 
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;

    // エフェクト 
    std::unique_ptr<DirectX::BasicEffect> m_BatchEffect;

    // プリミティブバッチ 
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_Batch;
    //DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* m_Batch;
    // 現在のHP
    float m_currentHP;
    // 最大HP
    float m_maxHP;

public:
    HPUI(ID3D11Device1* device);
    ~HPUI();

    void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
    void Finalize();

    void SetPosition(const DirectX::SimpleMath::Vector3& pos);
    void SetScale(const float& ratio);
    void SetHP(float currentHP, float maxHP);
};