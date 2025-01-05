/*
    ファイル名：StageEnemy.cpp
    　　　概要：ステージの敵を管理するクラス
*/
#include "pch.h"
#include "StageEnemy.h"
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageEnemy::StageEnemy(Player* player)
    : m_player(player)
    , m_isChangeStage(false) 
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageEnemy::~StageEnemy()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageEnemy::Initialize(const std::string& stageName)
{
    using json = nlohmann::json;

    // 既存の敵を削除
    m_enemies.clear();

    // JSONデータの読み込み
    std::ifstream file("Resources/EnemyData/EnemyData1.json");

    // 読み込めない場合は処理をスキップ
    if (!file.is_open()) 
    {
        return;
    }

    json stageData;
    file >> stageData;  // JSONデータを読み込む

    // ステージデータを取得
    // ステージが存在したら
    if (stageData.contains(stageName))
    {
        // 敵データを全て処理する
        for (const auto& enemyData : stageData[stageName])
        {
            // 敵の種類を取得する
            std::string type = enemyData["type"];

            // 敵の位置を取得する
            DirectX::SimpleMath::Vector3 position
            (
                enemyData["position"][0].get<float>(),
                enemyData["position"][1].get<float>(),
                enemyData["position"][2].get<float>()
            );

            // ファクトリーで敵を生成
            auto enemy = EnemyFactory::CreateEnemy(type, m_player);
            if (enemy)
            {
                enemy->Initialize(position);
                m_enemies.push_back(std::move(enemy));
            }
        }
    }
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageEnemy::Update()
{
    m_isChangeStage = true;  // ステージ遷移フラグをON

    for (auto& enemy : m_enemies) 
    {
        if (enemy->IsAlive())
        {
            enemy->Update();
            m_isChangeStage = false;  // 敵が生きていたらフラグをOFF
        }
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageEnemy::Render() 
{
    for (auto& enemy : m_enemies)
    {
        if (enemy->IsAlive())
        {
            enemy->Render();
        }
    }
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void StageEnemy::Finalize() 
{
    for (auto& enemy : m_enemies) 
    {
        enemy->Finalize();
    }
}
