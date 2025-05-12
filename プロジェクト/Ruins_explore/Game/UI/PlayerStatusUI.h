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
    PlayerStatusUI();
    // デストラクタ
    ~PlayerStatusUI();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    // ステータスアイコンの位置
    const DirectX::SimpleMath::Vector2 STATUS_ICON_POS = DirectX::SimpleMath::Vector2(10.f, 10.f);
    // 体力表示位置の原点
    const DirectX::SimpleMath::Vector2 HEALTH_POS_ORIGIN = DirectX::SimpleMath::Vector2(108.f, 10.f);
    // 体力表示一つずつの距離
    const float HEALTH_SHIFT_LENGTH = 53.f;
    // スタミナ表示位置の原点
    const DirectX::SimpleMath::Vector2 STAMINA_POS_ORIGIN = DirectX::SimpleMath::Vector2(130.f, 60.f);
    // 体力表示一つずつの距離
    const float STAMINA_SHIFT_LENGTH = 50.f;

private:
    // プレイヤー
    Player* m_player;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // 体力(赤色)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hearthRed_Tex;
    // 体力(灰色)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_hearthGray_Tex;
    // スタミナ(黄色)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_staminaYellow_Tex;
    // スタミナ(灰色)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_staminaGray_Tex;
    // ステータスアイコン
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_statusIcon_Tex;
    // スケール
    float m_scale;
    // 体力の位置
    DirectX::SimpleMath::Vector2 m_healthPosition[6];
    // スタミナの位置
    DirectX::SimpleMath::Vector2 m_staminaPosition[6];
};
