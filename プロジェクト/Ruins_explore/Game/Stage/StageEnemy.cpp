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
    m_enemies.clear();  // �����̓G���폜

    // JSON�f�[�^�̓ǂݍ���
    std::ifstream file("Resources/EnemyData1.json");
    /*if (!file.is_open()) 
    {
        std::cerr << "Failed to open stage data file!" << std::endl;
        return;
    }*/

    json stageData;
    file >> stageData;  // JSON�f�[�^��ǂݍ���

    // �X�e�[�W�f�[�^���擾
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

            // �t�@�N�g���[���g���ēG�𐶐�
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
    m_isChangeScene = false;  // �V�[���J�ڃt���O��ON

    for (auto& enemy : m_enemies) 
    {
        enemy->Update();
        //if (!enemy->IsAlive()) {
        //    m_isChangeScene = false;  // �G���S�ł�����t���O��OFF
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
