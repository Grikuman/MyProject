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
    // 選択フラグでの処理をする
    void SelectFlagProcess();

private:
    // タイトル文字の位置
    const DirectX::SimpleMath::Vector2 TITLETEXT_POS = DirectX::SimpleMath::Vector2(260, 80);
    // 『プレイする』文字の位置
    const DirectX::SimpleMath::Vector2 PLAYTEXT_POS = DirectX::SimpleMath::Vector2(450, 360);
    // 『終了する』文字の位置
    const DirectX::SimpleMath::Vector2 ENDTEXT_POS = DirectX::SimpleMath::Vector2(420, 480);
    // 『スペースキーで決定する』文字の位置
    const DirectX::SimpleMath::Vector2 SPACECONFILMTEXT_POS = DirectX::SimpleMath::Vector2(440, 650);
    // 選択矢印の位置
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_1 = DirectX::SimpleMath::Vector2(400, 390);
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_2 = DirectX::SimpleMath::Vector2(400, 510);
    // タイトル背景の位置
    const DirectX::SimpleMath::Vector2 BACKGROUND_POS = DirectX::SimpleMath::Vector2(0,0);
private:
    // タイトルシーン
    TitleScene* m_titleScene;
    // スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // 『Ruins Explorer』文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleText_Tex;
    // 『プレイする』文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playText_Tex;
    // 『終了する』文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_endText_Tex;
    // 『スペースキーで決定する』文字
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SpaceConfilmText_Tex;
    // 選択矢印
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectArrow_Tex;
    // タイトル背景
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround_Tex;
    // セレクトフラグ
    bool m_selectFlag;
    // 文字の点滅
    float m_alpha;
    // 点滅用の色
    DirectX::SimpleMath::Vector4 m_color;
    // 選択矢印の位置
    DirectX::SimpleMath::Vector2 m_selectArrowPos;
};
