/*
    ファイル名：MapSelectUI.h
    　　　概要：マップセレクトのUIを管理するクラス
*/
#pragma once

class MapSelectScene;

class MapSelectUI
{
public:
    // コンストラクタ
    MapSelectUI(MapSelectScene* mapSelectScene);
    // デストラクタ
    ~MapSelectUI();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    // 選択フラグの処理をする
    void SelectFlagProcess();
    // ポップアップの描画をする
    void PopupRender();

private:
    // 選択メニューの位置
    const DirectX::SimpleMath::Vector2 SELECTMENU_POS = DirectX::SimpleMath::Vector2(0, 0);
    // クエスト選択矢印の位置
    const DirectX::SimpleMath::Vector2 ARROW_POS[2] =
    {
        { 50,130 },
        { 50,190 }
    };
    // ポップアップ選択矢印の位置
    const DirectX::SimpleMath::Vector2 POPUP_ARROW_POS[2] =
    {
        { 470,640 },
        { 600,640 }
    };
    // チュートリアルのアイコンの位置
    const DirectX::SimpleMath::Vector2 TUTORIALICON_POS = DirectX::SimpleMath::Vector2(100, 130);
    // ステージ1のアイコンの位置
    const DirectX::SimpleMath::Vector2 STAGE1ICON_POS = DirectX::SimpleMath::Vector2(100, 190);

    // ポップアップの位置
    const DirectX::SimpleMath::Vector2 POPUP_POS = { 430,600 };

private:
    // タイトルシーン
    MapSelectScene* m_mapSelectScene;;
    //スプライトバッチ
    DirectX::SpriteBatch* m_spriteBatch;
    // 選択メニューの画像
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SelectMenu_Tex;
    // 選択矢印の画像
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectArrow_Tex;
    // チュートリアルのアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tutorialIcon_Tex;
    // ステージ1のアイコン
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage1Icon_Tex;

    // クエスト受注ポップアップの画像
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_questPopup_Tex;

    // ステージの選択フラグ
    int m_selectFlag;
    // クエスト選択矢印の位置
    DirectX::SimpleMath::Vector2 m_questArrowPos;
    // ポップアップ選択矢印の位置
    DirectX::SimpleMath::Vector2 m_popupArrowPos;
    // ポップアップの表示フラグ
    bool m_popupViewFlag;
    // ポップアップ内の選択フラグ
    bool m_popupFlag;
};
