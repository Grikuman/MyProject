#include "pch.h"
#include "StageEnemy.h"
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

StageEnemy::StageEnemy(Player* player)
    : m_player(player)
    , m_isChangeScene(false) 
{

}

//---------------------------------------------------------
// 
//---------------------------------------------------------
void StageEnemy::Initialize(const std::string& stageName)
{
    m_enemies.clear();  // 既存の敵を削除

    // JSONデータの読み込み
    std::ifstream file("Resources/EnemyData1.json");
    /*if (!file.is_open()) 
    {
        std::cerr << "Failed to open stage data file!" << std::endl;
        return;
    }*/

    json stageData;
    file >> stageData;  // JSONデータを読み込む

    // ステージデータを取得
    if (stageData.contains(stageName))
    {
        for (const auto& enemyData : stageData[stageName])
        {
            std::string type = enemyData["type"];
            DirectX::SimpleMath::Vector3 position(
                enemyData["position"][0].get<float>(),
                enemyData["position"][1].get<float>(),
                enemyData["position"][2].get<float>()
            );

            // ファクトリーを使って敵を生成
            auto enemy = EnemyFactory::CreateEnemy(type, m_player);
            if (enemy)
            {
                enemy->Initialize(position);
                m_enemies.push_back(std::move(enemy));
            }
        }
    }
    else {
        std::cerr << "Stage name not found in the data!" << std::endl;
    }
}

//---------------------------------------------------------
// 
//---------------------------------------------------------
void StageEnemy::Update() {
    m_isChangeScene = false;  // シーン遷移フラグをON

    for (auto& enemy : m_enemies) 
    {
        enemy->Update();
        //if (!enemy->IsAlive()) {
        //    m_isChangeScene = false;  // 敵が全滅したらフラグをOFF
        //}
    }
}

//---------------------------------------------------------
// 
//---------------------------------------------------------
void StageEnemy::Render() 
{
    for (auto& enemy : m_enemies)
    {
        enemy->Render();
    }
}

//---------------------------------------------------------
// 
//---------------------------------------------------------
void StageEnemy::Finalize() 
{
    for (auto& enemy : m_enemies) 
    {
        enemy->Finalize();
    }
}

//---------------------------------------------------------
// 
//---------------------------------------------------------
bool StageEnemy::IsChangeScene() const {
    return m_isChangeScene;
}
