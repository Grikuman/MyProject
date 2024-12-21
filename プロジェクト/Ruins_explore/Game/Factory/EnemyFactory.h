/*
    �t�@�C�����FEnemyFactory.h
    �@�@�@�T�v�F�G�𐶐�����N���X
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"

class EnemyFactory 
{
public:
    // �G�𐶐�����
    static std::unique_ptr<IEnemy> CreateEnemy(const std::string& type, Player* player) 
    {
        // �G�^�C�v�������ɒǉ�
        if (type == "Tunomaru") 
        {
            return std::make_unique<Tunomaru>(player);
        }
        else if (type == "RockBoss") 
        {
            return std::make_unique<RockBoss>(player);
        }
        
        return nullptr;  // �G�^�C�v�����Ȃ��ꍇ
    }
};

