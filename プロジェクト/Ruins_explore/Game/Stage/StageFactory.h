#include <unordered_map>
#include <functional>
#include <memory>
#include "Game/Interface/IStage.h"

#include "Game/Stage/Stage1_1.h"
#include "game/Stage/Stage1_2.h"

// �X�e�[�W�����t�@�N�g��
class StageFactory {
public:
    // �X�e�[�W�쐬����
    static std::unique_ptr<IStage> CreateStage(StageID id) 
    {
        static std::unordered_map<
            StageID, 
            std::function<std::unique_ptr<IStage>()>> stageMap = 
        {
            { StageID::Stage1_1, []() { return std::make_unique<Stage1_1>(); } },
            { StageID::Stage1_2, []() { return std::make_unique<Stage1_2>(); } },
        };

        // ID����X�e�[�W������
        auto it = stageMap.find(id);
        if (it != stageMap.end()) {
            return it->second();
        }
        return nullptr; // ������ID�̏ꍇnull��Ԃ�
    }
};

