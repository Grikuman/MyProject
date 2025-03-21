#include "pch.h"
#include "Audio.h"
#include <iostream>

// シングルトンインスタンス
std::unique_ptr<Audio> Audio::m_audio = nullptr;

//---------------------------------------------------------
// インスタンスを取得する
//---------------------------------------------------------
Audio* const Audio::GetInstance()
{
    if (!m_audio)
    {
        m_audio.reset(new Audio());
    }
    return m_audio.get();
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Audio::Audio()
    : m_system(nullptr),
    m_bgmChannel(nullptr),
    m_seChannel(nullptr)
{
    FMOD::System_Create(&m_system);
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Audio::Initialize()
{
    // FMODシステムの初期化（最大512チャネル、通常モード）
    m_system->init(512, FMOD_INIT_NORMAL, nullptr);
    // BGMを読み込む
    LoadBGM("TitleBGM", "Resources/Sounds/TitleBGM.mp3");
    LoadBGM("TutorialBGM", "Resources/Sounds/TutorialBGM.mp3");
    LoadBGM("BattleBGM_1", "Resources/Sounds/BattleBGM_1.mp3");
    LoadBGM("StageClearBGM", "Resources/Sounds/StageClearBGM.mp3");
    LoadBGM("StageFailedBGM", "Resources/Sounds/StageFailedBGM.mp3");

    // SEを読み込む
    LoadSE("PunchHitSE", "Resources/Sounds/PunchHitSE.mp3");
    LoadSE("PunchSE", "Resources/Sounds/PunchSE.mp3");
    LoadSE("DashSE", "Resources/Sounds/DashSE.mp3");
    LoadSE("EnemyAttackSE", "Resources/Sounds/EnemyAttackSE.mp3");
    LoadSE("MenuSelectSE", "Resources/Sounds/MenuSelectSE.mp3");
    LoadSE("QuestSelectSE1", "Resources/Sounds/QuestSelectSE1.mp3");
    LoadSE("QuestSelectSE2", "Resources/Sounds/QuestSelectSE2.mp3");
    LoadSE("QuestSelectSE3", "Resources/Sounds/QuestSelectSE3.mp3");
    LoadSE("QuestStartSE", "Resources/Sounds/QuestStartSE.mp3");
}

//---------------------------------------------------------
// BGMを読み込む
//---------------------------------------------------------
void Audio::LoadBGM(const std::string& name, const char* filename)
{
    FMOD::Sound* sound = nullptr;
    m_system->createSound(filename, FMOD_LOOP_NORMAL, nullptr, &sound);
    if (sound)
    {
        m_bgm[name] = sound;
    }
}

//---------------------------------------------------------
// SEを読み込む
//---------------------------------------------------------
void Audio::LoadSE(const std::string& name, const char* filename)
{
    FMOD::Sound* sound = nullptr;
    m_system->createSound(filename, FMOD_DEFAULT, nullptr, &sound);
    if (sound)
    {
        m_se[name] = sound;
    }
}

//---------------------------------------------------------
// BGMを再生する
//---------------------------------------------------------
void Audio::PlayBGM(const std::string& name, float volume)
{
    // 現在のBGMを停止
    if (m_bgmChannel)
    {
        m_bgmChannel->stop();
    }

    auto it = m_bgm.find(name);
    if (it != m_bgm.end())
    {
        m_system->playSound(it->second, nullptr, false, &m_bgmChannel);

        // 再生後に音量を調整
        if (m_bgmChannel)
        {
            m_bgmChannel->setVolume(volume);
        }
    }
}


//---------------------------------------------------------
// SEを再生する
//---------------------------------------------------------
void Audio::PlaySE(const std::string& name)
{
    auto it = m_se.find(name);
    if (it != m_se.end())
    {
        m_system->playSound(it->second, nullptr, false, &m_seChannel);
    }
}

//---------------------------------------------------------
// BGMを停止する
//---------------------------------------------------------
void Audio::StopBGM()
{
    // 現在のBGMを停止
    if (m_bgmChannel)
    {
        m_bgmChannel->stop();
    }
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Audio::Update()
{
    m_system->update();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Audio::Finalize()
{
    for (auto& bgm : m_bgm)
    {
        bgm.second->release();
    }
    m_bgm.clear();

    for (auto& se : m_se)
    {
        se.second->release();
    }
    m_se.clear();

    m_system->close();
    m_system->release();
}
