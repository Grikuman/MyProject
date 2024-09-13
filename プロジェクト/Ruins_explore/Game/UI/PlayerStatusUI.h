/*
    @file    PlayerStatusUI.h
    @brief   プレイヤーのUIを管理するクラス
*/
#pragma once

// 前方宣言
class Player;

class PlayerStatusUI
{
public:
    // コンストラクタ
    PlayerStatusUI(Player* player);
    // デストラクタ
    ~PlayerStatusUI();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();
private:
    // Player
    Player* m_player;

    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // 体力(赤色)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tex_HealthRed[6];
    // 体力(灰色)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_tex_HealthGray[6];
    // スタミナ(黄色)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_tex_StaminaYellow[6];
    // スタミナ(灰色)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_tex_StaminaGray[6];
    // ステータスアイコン
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_tex_StatusIcon;
    // 体力ゲージの枠
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_tex_HelthGaugeFrame;
    // スタミナゲージの枠
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_tex_StaminaGaugeFrame;

    // スケール
    float m_scale;
    // HPの表示割合(matrix)
    DirectX::SimpleMath::Matrix m_matrix;

    // 体力の位置
    DirectX::SimpleMath::Vector2 m_healthPosition[6];
    // スタミナの位置
    DirectX::SimpleMath::Vector2 m_staminaPosition[6];
    // ステータスアイコンの位置
    DirectX::SimpleMath::Vector2 m_backPosition;
    // ゲージの枠の位置
    DirectX::SimpleMath::Vector2 m_framePosition;
};
