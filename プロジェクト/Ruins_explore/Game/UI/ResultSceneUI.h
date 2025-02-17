/*
    ファイル名：ResultSceneUI.h
    　　　概要：リザルトシーンのUIを管理するクラス
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
    // クリア文字の位置
    const DirectX::SimpleMath::Vector2 CLEAR_TEXT_POS = DirectX::SimpleMath::Vector2(200, 50);
    // 死亡文字の位置
    const DirectX::SimpleMath::Vector2 DEAD_TEXT_POS = DirectX::SimpleMath::Vector2(200, 50);
    // クリア画像の位置
    const DirectX::SimpleMath::Vector2 CLEAR_POS = DirectX::SimpleMath::Vector2(0,0);
    // 死亡画像の位置
    const DirectX::SimpleMath::Vector2 DEAD_POS = DirectX::SimpleMath::Vector2(0,0);
    // スペースキー文字の位置
    const DirectX::SimpleMath::Vector2 SPACEKEY_TEXT_POS = DirectX::SimpleMath::Vector2(400, 580);
    // スペースキー文字の色調整
    const float SPACEKEY_TEXT_COLOR_R = 0.9f;
    const float SPACEKEY_TEXT_COLOR_G = 0.9f;
    const float SPACEKEY_TEXT_COLOR_B = 0.9f;

private:
    // タイトルシーン
    ResultScene* m_resultScene;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // クリア文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clearText_Tex;
    // 死亡文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_deadText_Tex;
    // リザルトクリア画面
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear_Tex;
    // リザルト死亡画面
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_dead_Tex;
    // スペースキー
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_spaceKeyText_Tex;

    // スペースキーのアルファ値
    float m_spaceAlpha;
    // 時間
    float m_time;
};
