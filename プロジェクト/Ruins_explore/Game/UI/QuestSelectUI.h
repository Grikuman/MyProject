/*
    ファイル名：QuestSelectUI.h
    　　　概要：クエスト選択のUIを管理するクラス
*/
#pragma once

class QuestSelectUI
{
public:
    // クエストを開始するかどうか取得する
    bool GetQuestStart() { return m_questStart; }

public:
    // コンストラクタ
    QuestSelectUI();
    // デストラクタ
    ~QuestSelectUI();
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
    const DirectX::SimpleMath::Vector2 SELECTMENU_POS = { 0.0f, 0.0f };
    // チュートリアルのアイコンの位置
    const DirectX::SimpleMath::Vector2 TUTORIALICON_POS = { 100.0f, 130.0f };
    // ステージ1のアイコンの位置
    const DirectX::SimpleMath::Vector2 STAGE1ICON_POS = { 100.0f, 190.0f };
    // クエスト選択矢印の位置
    const DirectX::SimpleMath::Vector2 ARROW_POS[2] =
    {
        { 50,130 },
        { 50,190 }
    };
    // ポップアップの位置
    const DirectX::SimpleMath::Vector2 POPUP_POS = { 430,300 };
    // ポップアップ選択矢印の位置
    const DirectX::SimpleMath::Vector2 POPUP_ARROW_POS[2] =
    {
        { 470,340 },
        { 600,340 }
    };
    // クエストボードの位置
    const DirectX::SimpleMath::Vector2 QUEST_BOARD_POS = { 750,70 };

private:
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
    // クエストボードの画像
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_questBoard_Tex[2];
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
    // クエスト開始フラグ
    bool m_questStart;
};
