#include <unordered_map>
#include <functional>
#include <memory>
#include "Game/Interface/IStage.h"

#include "Game/Stage/Stage1_1.h"
#include "game/Stage/Stage1_2.h"

// ステージ生成ファクトリ
class StageFactory {
public:
    // ステージ作成する
    static std::unique_ptr<IStage> CreateStage(StageID id) 
    {
        static std::unordered_map<
            StageID, 
            std::function<std::unique_ptr<IStage>()>> stageMap = 
        {
            { StageID::Stage1_1, []() { return std::make_unique<Stage1_1>(); } },
            { StageID::Stage1_2, []() { return std::make_unique<Stage1_2>(); } },
        };

        // IDからステージを検索
        auto it = stageMap.find(id);
        if (it != stageMap.end()) {
            return it->second();
        }
        return nullptr; // 無効なIDの場合nullを返す
    }
};

