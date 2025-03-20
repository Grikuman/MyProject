/*
    �t�@�C�����FStageFactory.h
    �@�@�@�T�v�F�X�e�[�W�𐶐�����N���X
*/
#include <unordered_map>
#include <functional>
#include <memory>
#include "Game/Interface/IStage.h"
#include <string>

#include "Game/Stage/TutorialStage.h"
#include "Game/Stage/Stage1_1.h"
#include "game/Stage/Stage1_2.h"

// �X�e�[�W�����t�@�N�g��
class StageFactory 
{
public:
    // �X�e�[�W�쐬����
    static std::unique_ptr<IStage> CreateStage(StageID id) 
    {
        // ���I�Ɉ��� function
        // �X�e�[�W���i�[����ϐ�
        static std::unordered_map<StageID, std::function<std::unique_ptr<IStage>()>> stageMap = 
        {
            { StageID::TutorialStage, []() { return std::make_unique<TutorialStage>("TutorialStage"); }},
            { StageID::Stage1_1, []() { return std::make_unique<Stage1_1>("Stage1_1"); }},
            { StageID::Stage1_2, []() { return std::make_unique<Stage1_2>("Stage1_2"); }},
        };

        // ID����X�e�[�W���������ĕԂ�
        auto it = stageMap.find(id);
        if (it != stageMap.end()) {
            return it->second();
        }
        return nullptr; // ������ID�̏ꍇnull��Ԃ�
    }
};

