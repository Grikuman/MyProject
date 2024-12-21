/*
    ファイル名：EnemyFactory.h
    　　　概要：敵を生成するクラス
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"

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
        else if (type == "RockBoss") 
        {
            return std::make_unique<RockBoss>(player);
        }
        
        return nullptr;  // 敵タイプがいない場合
    }
};

