/*
    �t�@�C�����FEnemyFactory.h
    �@�@�@�T�v�F�G�𐶐�����N���X
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Enemy/Tunomaru/Tunomaru.h"
#include "Game/Enemy/NeedleBoss/NeedleBoss.h"
#include "Game/Enemy/Mutant/Mutant.h"

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
        else if (type == "NeedleBoss")
        {
            return std::make_unique<NeedleBoss>(player);
        }
        else if (type == "Mutant")
        {
            return std::make_unique<Mutant>(player);
        }
        
        return nullptr;  // �G�^�C�v�����Ȃ��ꍇ
    }
};

