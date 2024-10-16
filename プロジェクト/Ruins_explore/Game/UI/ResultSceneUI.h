/*
    @file    ResultSceneUI.h
    @brief   プレイヤーのUIを管理するクラス
*/
#pragma once

class ResultScene;

class ResultSceneUI
{
public:
    // コンストラクタ
    ResultSceneUI(ResultScene* result);
    // デストラクタ
    ~ResultSceneUI();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();

private:
    // タイトルシーン
    ResultScene* m_resultScene;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // セレクトアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectIcon;
    // クリア文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear;
    // 死亡文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_dead;
    // リザルトクリア画面
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultClear;
    // リザルト死亡画面
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultDead;
    // 黒
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_black;
    // スペースキー
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushSpaceKey;

    // セレクト位置
    DirectX::SimpleMath::Vector2 m_selectPos;
    // セレクトフラグ
    bool m_selectFlag;
    // アルファ値
    float m_alpha;
    // スペースキーのアルファ値
    float m_spaceAlpha;
    // フェードフラグ
    bool m_fadeFlag;
    // 時間
    float m_time;
};
