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
    // 後処理する
    void Finalize();

private:
    // タイトルシーン
    MapSelectScene* m_mapSelectScene;;
    //スプライトバッチ
    DirectX::DX11::SpriteBatch* m_spriteBatch;
};
