/*
    @file    TitleSceneUI.h
    @brief   プレイヤーのUIを管理するクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class Player;

class TitleSceneUI
{
public:
    // コンストラクタ
    TitleSceneUI(Player* player);
    // デストラクタ
    ~TitleSceneUI();
    // 初期化する
    void Initialize(CommonResources* resources);
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();
private:
    // 共通リソース
    CommonResources* m_commonResources;
    // Player
    Player* m_player;
    //スプライトバッチ
    std::unique_ptr<DirectX::DX11::SpriteBatch> m_spriteBatch;

    // 背景
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tex_backGround;

    // 背景の位置
    DirectX::SimpleMath::Vector2 m_backGroundPos;
};
