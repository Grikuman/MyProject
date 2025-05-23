/*
    ファイル名：StageCollision.h
    　　　概要：ステージのオブジェクトを管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemy.h"

// 前方宣言
class Player;

class StageCollision
{
public:
    // コンストラクタ
    StageCollision(Player* player);
    // デストラクタ
    ~StageCollision();
    // 初期化処理（ステージ名を指定）
    void Initialize(const std::string& stageName);
    //更新処理
    void Update(std::vector<std::unique_ptr<IEnemy>>& enemies);
    // 描画処理
    void Render();
    // 終了処理
    void Finalize();

private:
    // オブジェクトのデータ構造体
    struct ModelData
    {
        std::string name;                      // モデル名
        DirectX::SimpleMath::Vector3 position; // 配置位置
        DirectX::SimpleMath::Vector3 rotation; // 回転角度
        DirectX::SimpleMath::Vector3 scale;    // スケール倍率
        DirectX::BoundingBox m_boundingBox;    // バウンディングボックス
        DirectX::Model* m_model;               // モデルデータ
    };

private:
    // 描画するかどうか(true:描画する.false:描画しない)
    static const bool VIEW = false;

private:
    // ステージ内のモデルリスト
    std::vector<ModelData> m_models;
    // プレイヤー
    Player* m_player;
    // 描画判断
    bool m_view;
};
