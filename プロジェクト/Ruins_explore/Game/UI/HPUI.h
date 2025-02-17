#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

class HPUI 
{
public:
    // コンストラクタ
    HPUI(ID3D11Device1* device);
    // デストラクタ
    ~HPUI();
    // 更新する
    void Update();
    // 描画する
    void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
    // 終了処理
    void Finalize();
    // 
    void SetPosition(const DirectX::SimpleMath::Vector3& pos);
    void SetScale(const float& ratio);
    void SetHP(float currentHP, float maxHP);

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
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    //共通ステートオブジェクトへのポインタ
    std::unique_ptr<DirectX::CommonStates> m_states;
    // エフェクト 
    std::unique_ptr<DirectX::BasicEffect> m_batchEffect;
    // プリミティブバッチ 
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
    // 現在のHP
    float m_currentHP;
    // 最大HP
    float m_maxHP;
};