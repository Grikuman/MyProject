#include "pch.h"
#include "Audio.h"
#include <iostream>

// �V���O���g���C���X�^���X
std::unique_ptr<Audio> Audio::m_audio = nullptr;

//---------------------------------------------------------
// �C���X�^���X���擾����
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
// �R���X�g���N�^
//---------------------------------------------------------
Audio::Audio()
    : m_system(nullptr),
    m_bgmChannel(nullptr),
    m_seChannel(nullptr)
{
    FMOD::System_Create(&m_system);
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Audio::Initialize()
{
    // FMOD�V�X�e���̏������i�ő�512�`���l���A�ʏ탂�[�h�j
    m_system->init(512, FMOD_INIT_NORMAL, nullptr);
    // BGM��ǂݍ���
    LoadBGM("TitleBGM", "Resources/Sounds/TitleBGM.mp3");
    LoadBGM("TutorialBGM", "Resources/Sounds/TutorialBGM.mp3");
    LoadBGM("BattleBGM_1", "Resources/Sounds/BattleBGM_1.mp3");
    LoadBGM("StageClearBGM", "Resources/Sounds/StageClearBGM.mp3");
    LoadBGM("StageFailedBGM", "Resources/Sounds/StageFailedBGM.mp3");

    // SE��ǂݍ���
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
// BGM��ǂݍ���
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
// SE��ǂݍ���
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
// BGM���Đ�����
//---------------------------------------------------------
void Audio::PlayBGM(const std::string& name, float volume)
{
    // ���݂�BGM���~
    if (m_bgmChannel)
    {
        m_bgmChannel->stop();
    }

    auto it = m_bgm.find(name);
    if (it != m_bgm.end())
    {
        m_system->playSound(it->second, nullptr, false, &m_bgmChannel);

        // �Đ���ɉ��ʂ𒲐�
        if (m_bgmChannel)
        {
            m_bgmChannel->setVolume(volume);
        }
    }
}


//---------------------------------------------------------
// SE���Đ�����
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
// BGM���~����
//---------------------------------------------------------
void Audio::StopBGM()
{
    // ���݂�BGM���~
    if (m_bgmChannel)
    {
        m_bgmChannel->stop();
    }
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Audio::Update()
{
    m_system->update();
}

//---------------------------------------------------------
// �I������
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
