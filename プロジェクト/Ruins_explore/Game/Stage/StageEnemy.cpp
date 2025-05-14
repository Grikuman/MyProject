/*
    ファイル名：StageEnemy.cpp
    　　　概要：ステージの敵を管理するクラス
*/
#include "pch.h"
#include "StageEnemy.h"
#include "Game/Factory/EnemyFactory.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageEnemy::StageEnemy()
    :
    m_enemies{},
    m_isChangeStage{ false }
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
    // ファイルを読み込む
    LoadFile(stageName);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageEnemy::Update()
{
    m_isChangeStage = true;  // ステージ遷移フラグをON

    // 敵を更新する
    for (auto& enemy : m_enemies) 
    {
        // 生存している場合のみ
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
    // 敵を描画する
    for (auto& enemy : m_enemies)
    {
        // 生存している場合のみ
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
    // 敵の終了処理
    for (auto& enemy : m_enemies) 
    {
        enemy->Finalize();
    }
}

//---------------------------------------------------------
// ファイルを読み込む
//---------------------------------------------------------
void StageEnemy::LoadFile(const std::string& stageName)
{
    using json = nlohmann::json;

    // 既存の敵を削除
    m_enemies.clear();
    // JSONデータの読み込み
    std::ifstream file("Resources/StageEnemyData/EnemyData1.json");

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
            auto enemy = EnemyFactory::CreateEnemy(type);
            if (enemy)
            {
                // 敵を初期化する
                enemy->Initialize(position);
                // 敵をリストに登録
                m_enemies.push_back(std::move(enemy));
            }
        }
    }
}
