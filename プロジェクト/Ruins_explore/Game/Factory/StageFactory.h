/*
    ファイル名：StageFactory.h
    　　　概要：ステージを生成するクラス
*/
#include <unordered_map>
#include <functional>
#include <memory>
#include "Game/Interface/IStage.h"
#include <string>

#include "Game/Stage/TutorialStage.h"
#include "Game/Stage/Stage1.h"

// ステージ生成ファクトリ
class StageFactory 
{
public:
    // ステージ作成する
    static std::unique_ptr<IStage> CreateStage(StageID id) 
    {
        // 動的に扱う function
        // ステージを格納する変数
        static std::unordered_map<StageID, std::function<std::unique_ptr<IStage>()>> stageMap = 
        {
            { StageID::TutorialStage, []() { return std::make_unique<TutorialStage>("TutorialStage"); }},
            { StageID::Stage1, []() { return std::make_unique<Stage1>("Stage1"); }},
        };

        // IDからステージを検索して返す
        auto it = stageMap.find(id);
        if (it != stageMap.end()) {
            return it->second();
        }
        return nullptr; // 無効なIDの場合nullを返す
    }
};

