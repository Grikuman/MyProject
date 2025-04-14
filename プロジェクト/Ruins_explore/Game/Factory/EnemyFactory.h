/*
    ファイル名：EnemyFactory.h
    　　　概要：敵を生成するクラス
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Enemy/Tunomaru/Tunomaru.h"
#include "Game/Enemy/NeedleBoss/NeedleBoss.h"
#include "Game/Enemy/Mutant/Mutant.h"

class EnemyFactory 
{
public:
    // 敵を生成する
    static std::unique_ptr<IEnemy> CreateEnemy(const std::string& type, Player* player) 
    {
        // 敵タイプをここに追加
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
        
        return nullptr;  // 敵タイプがいない場合
    }
};

