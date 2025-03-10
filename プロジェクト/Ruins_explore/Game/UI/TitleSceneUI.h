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
    // ゲームタイトルの位置
    const DirectX::SimpleMath::Vector2 GAMETITLE_POS = DirectX::SimpleMath::Vector2(350, 150);
    // 選択文字の位置
    const DirectX::SimpleMath::Vector2 SELECT_POS = DirectX::SimpleMath::Vector2(450, 400);
    // 選択矢印の位置
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_1 = DirectX::SimpleMath::Vector2(500, 390);
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_2 = DirectX::SimpleMath::Vector2(500, 510);
    // i文字の位置
    const DirectX::SimpleMath::Vector2 I_POS = DirectX::SimpleMath::Vector2(485, 210);
    // o文字の位置
    const DirectX::SimpleMath::Vector2 O_POS = DirectX::SimpleMath::Vector2(810, 255);
    // i・oの回転中心位置
    const DirectX::SimpleMath::Vector2 I_CENTER_POS = DirectX::SimpleMath::Vector2(25, 25);
    const DirectX::SimpleMath::Vector2 O_CENTER_POS = DirectX::SimpleMath::Vector2(25, 25);
    // タイトル背景の位置
    const DirectX::SimpleMath::Vector2 BACKGROUND_POS = DirectX::SimpleMath::Vector2(0,0);


private:
    // タイトルシーン
    TitleScene* m_titleScene;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // ゲームタイトル
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_gameTitle_Tex;
    // 選択文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_select_Tex;
    // 選択矢印
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectArrow_Tex;
    // i・oの回転文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_i_Tex;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_o_Tex;
    // 背景
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround_Tex;
    // セレクトフラグ
    bool m_selectFlag;
    // 回転
    float m_rotate;
    // 選択矢印の位置
    DirectX::SimpleMath::Vector2 m_selectArrowPos;
};
