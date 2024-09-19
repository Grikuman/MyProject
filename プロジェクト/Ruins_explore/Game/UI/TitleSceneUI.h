/*
    @file    TitleSceneUI.h
    @brief   プレイヤーのUIを管理するクラス
*/
#pragma once

class TitleSceneUI
{
public:
    // コンストラクタ
    TitleSceneUI();
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
public:
    // シーン遷移
    bool ChangeScene() const { return m_changeSceneFlag; }
private:
    // シーン遷移フラグ
    bool m_changeSceneFlag;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // タイトル文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ruinsExplorer;
    // タイトルセレクト
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleSelect;
    // セレクトアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectIcon;

    // セレクト位置
    DirectX::SimpleMath::Vector2 m_selectPos;
    // セレクトフラグ
    bool m_selectFlag;
};
