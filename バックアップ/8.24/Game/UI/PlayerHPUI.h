/*
    @file    PlayerHPUI.h
    @brief   プレイヤーのUIを管理するクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class Player;

class PlayerHPUI
{
public:
    // コンストラクタ
    PlayerHPUI(Player* player);
    // デストラクタ
    ~PlayerHPUI();
    // 初期化する
    void Initialize(CommonResources* resources);
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();
private:
    // 共通リソース
    CommonResources* m_commonResources;
    // Player
    Player* m_player;

    //スプライトバッチ
    std::unique_ptr<DirectX::DX11::SpriteBatch> m_spriteBatch;
    // 体力(緑)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tex_Green;
    // 体力(赤)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_tex_Red;
    // 背景
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_tex_BackGround;


    // プレイヤーの体力
    float m_hp;
    // プレイヤーの最大体力
    const float MAXHP;
    // 位置
    DirectX::SimpleMath::Vector2 m_position;
    // スケール
    float m_scale;
    // HPの表示割合(matrix)
    DirectX::SimpleMath::Matrix m_matrix;

    // 背景の位置
    DirectX::SimpleMath::Vector2 m_backPosition;
};
