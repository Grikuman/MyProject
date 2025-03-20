/*
    ファイル名：TutorialGuideUI.h
    　　　概要：チュートリアルのUIを管理するクラス
*/
#pragma once

class TutorialGuideUI
{
public:
    // ミッションをクリアする(ミッション番号を指定)
    void ClearMission(int number) { m_missionFlag[number] = true; }

public:
    // ミッションクリア状況を取得する
    int GetMissionFlag(int number) { return m_missionFlag[number]; }

public:
    // コンストラクタ
    TutorialGuideUI();
    // デストラクタ
    ~TutorialGuideUI();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 終了処理
    void Finalize();

private:
    // ガイドミッションの位置
    const DirectX::SimpleMath::Vector2 GUIDEMISSION_POS = DirectX::SimpleMath::Vector2(10, 160);
    // チェックマークの位置
    const DirectX::SimpleMath::Vector2 MISSIONCHECKMARK_POS[4] = 
    {
        {10.0f, 150.0f},
        {10.0f, 205.0f},
        {10.0f, 263.0f},
        {10.0f, 320.0f} 
    };

private:
    //スプライトバッチ
    DirectX::SpriteBatch* m_spriteBatch;
    // ミッションの画像
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_guideMissionText_Tex;
    // ミッションのチェックマーク
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_missionCheckMark_Tex;
    // ミッションフラグ
    bool m_missionFlag[4];
    // ミッションのクリアカウント
    int m_missionClearCnt;
};
