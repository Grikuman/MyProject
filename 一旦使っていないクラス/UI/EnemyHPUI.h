#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

class EnemyHPUI 
{
public:
    // コンストラクタ
    EnemyHPUI(ID3D11Device1* device);
    // デストラクタ
    ~EnemyHPUI();
    // 初期化する
    void Initialize(const DirectX::SimpleMath::Vector3& position,const float& scale);
    // 更新する
    void Update(const DirectX::SimpleMath::Vector3& position, const float currentHP, const float maxHP);
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    // HPの緑色　：　サイズ
    const DirectX::VertexPositionColor VERTICES_GREEN[4] =
    {
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), DirectX::Colors::Green), //左上
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f,  1.0f, 0.0f), DirectX::Colors::Green),  //右上
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f, 0.5f, 0.0f), DirectX::Colors::Green),   //右下
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f, 0.5f, 0.0f), DirectX::Colors::Green),  //左下
    };
    // HPの赤色　：　サイズ
    const DirectX::VertexPositionColor VERTICES_RED[4] =
    {
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f),DirectX::Colors::Red),    //左上
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f,  1.0f, 0.0f), DirectX::Colors::Red),    //右上
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f, 0.5f, 0.0f),DirectX::Colors::Red),      //右下
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f, 0.5f, 0.0f),DirectX::Colors::Red),     //左下
    };

private:
    // 入力レイアウト 
    ID3D11InputLayout* m_inputLayout;
    // コモンステート
    DirectX::CommonStates* m_states;
    // エフェクト 
    DirectX::BasicEffect* m_batchEffect;
    // プリミティブバッチ 
    DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* m_primitiveBatch;
    //  座標用の変数を作る
    DirectX::SimpleMath::Vector3 m_position;
    // スケール
    float m_scale;
    // 現在のHP
    float m_currentHP;
    // 最大HP
    float m_maxHP;
};