#pragma once

class Player;

class StageObject
{
public:
    // コンストラクタとデストラクタ
    StageObject(Player* player);
    ~StageObject();

    // 初期化処理（ステージ名を指定）
    void Initialize(const std::string& stageName);

    //更新処理
    void Update();

    // 描画処理
    void Render();

    // 終了処理
    void Finalize();

private:
    struct ModelData
    {
        std::string name;                      // モデル名
        DirectX::SimpleMath::Vector3 position; // 配置位置
        DirectX::SimpleMath::Vector3 rotation; // 回転角度
        DirectX::SimpleMath::Vector3 scale;    // スケール倍率
        DirectX::BoundingBox m_boundingBox;    // バウンディングボックス
        DirectX::Model* m_model;               // モデルデータ
    };


    // ステージ内のモデルリスト
    std::vector<ModelData> m_models;

    // プレイヤー
    Player* m_player;
};
