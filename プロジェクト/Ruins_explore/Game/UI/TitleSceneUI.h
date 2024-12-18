/*
    ファイル名：TitleSceneUI.h
    　　　概要：タイトルシーンのUIを管理するクラス
*/
#pragma once

class TitleScene;

class TitleSceneUI
{
public:
    // コンストラクタ
    TitleSceneUI(TitleScene* titlescene);
    // デストラクタ
    ~TitleSceneUI();
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
    TitleScene* m_titleScene;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // タイトル文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ruinsExplorer;
    // タイトルセレクト
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleSelect;
    // セレクトアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectIcon;
    // i・oの文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_i_Rotate;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_o_Rotate;
    // タイトル背景
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleBackGround;
    // 黒
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_black;

    // セレクト位置
    DirectX::SimpleMath::Vector2 m_selectPos;
    // セレクトフラグ
    bool m_selectFlag;
    // 回転
    float m_rotate;
    // アルファ値
    float m_alpha;
    // フェードフラグ
    bool m_fadeFlag;
    // スケール
    float m_scale;
};
