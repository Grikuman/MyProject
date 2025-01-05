/*
    �t�@�C�����FStageEnemy.cpp
    �@�@�@�T�v�F�X�e�[�W�̓G���Ǘ�����N���X
*/
#include "pch.h"
#include "StageEnemy.h"
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageEnemy::StageEnemy(Player* player)
    : m_player(player)
    , m_isChangeStage(false) 
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageEnemy::~StageEnemy()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageEnemy::Initialize(const std::string& stageName)
{
    using json = nlohmann::json;

    // �����̓G���폜
    m_enemies.clear();

    // JSON�f�[�^�̓ǂݍ���
    std::ifstream file("Resources/EnemyData/EnemyData1.json");

    // �ǂݍ��߂Ȃ��ꍇ�͏������X�L�b�v
    if (!file.is_open()) 
    {
        return;
    }

    json stageData;
    file >> stageData;  // JSON�f�[�^��ǂݍ���

    // �X�e�[�W�f�[�^���擾
    // �X�e�[�W�����݂�����
    if (stageData.contains(stageName))
    {
        // �G�f�[�^��S�ď�������
        for (const auto& enemyData : stageData[stageName])
        {
            // �G�̎�ނ��擾����
            std::string type = enemyData["type"];

            // �G�̈ʒu���擾����
            DirectX::SimpleMath::Vector3 position
            (
                enemyData["position"][0].get<float>(),
                enemyData["position"][1].get<float>(),
                enemyData["position"][2].get<float>()
            );

            // �t�@�N�g���[�œG�𐶐�
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
// �X�V����
//---------------------------------------------------------
void StageEnemy::Update()
{
    m_isChangeStage = true;  // �X�e�[�W�J�ڃt���O��ON

    for (auto& enemy : m_enemies) 
    {
        if (enemy->IsAlive())
        {
            enemy->Update();
            m_isChangeStage = false;  // �G�������Ă�����t���O��OFF
        }
    }
}

//---------------------------------------------------------
// �`�悷��
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
// �I������
//---------------------------------------------------------
void StageEnemy::Finalize() 
{
    for (auto& enemy : m_enemies) 
    {
        enemy->Finalize();
    }
}
