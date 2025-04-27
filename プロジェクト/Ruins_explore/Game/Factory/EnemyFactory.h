/*
    ファイル名：EnemyFactory.h
    　　　概要：敵を生成するクラス
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Enemy/Mutant/Mutant.h"

class EnemyFactory 
{
public:
    // 敵を生成する
    static std::unique_ptr<IEnemy> CreateEnemy(const std::string& type, Player* player) 
    {
        // 敵タイプをここに追加
        if (type == "Mutant")
        {
            return std::make_unique<Mutant>(player);
        }
        
        return nullptr;  // 敵タイプがいない場合
    }
};

