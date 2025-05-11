/*
    �t�@�C�����FEnemyFactory.h
    �@�@�@�T�v�F�G�𐶐�����N���X
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Enemy/Warrok/Warrok.h"
#include "Game/Enemy/Demon/Demon.h"

class EnemyFactory 
{
public:
    // �G�𐶐�����
    static std::unique_ptr<IEnemy> CreateEnemy(const std::string& type, Player* player) 
    {
        // �G�^�C�v�������ɒǉ�
        if (type == "Mutant")
        {
            return std::make_unique<Mutant>(player);
        }
        else if (type == "Warrok")
        {
            return std::make_unique<Warrok>(player);
        }
        else if (type == "Demon")
        {
            return std::make_unique<Demon>(player);
        }
        
        return nullptr;  // �G�^�C�v�����Ȃ��ꍇ
    }
};

