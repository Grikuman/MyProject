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
    // * 各ステージの結果を描画する *
    void TutorialRender(); // チュートリアル
    void Stage1Render();   // ステージ1

private:
    // 背景の位置
    const DirectX::SimpleMath::Vector2 BACKGROUND_POS = { 0, 0 };
    // アイコンの表示する位置
    const DirectX::SimpleMath::Vector2 ICON_POS[2] =
    {
        { 500, 100 }, // チュートリアル
        { 420, 100 }  // ステージ1
    };

private:
    // タイトルシーン
    ResultScene* m_resultScene;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // 背景
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround_Tex;
    // チュートリアルクエストのアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tutorialIcon_Tex;
    // ステージ1のアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage1Icon_Tex;
};
