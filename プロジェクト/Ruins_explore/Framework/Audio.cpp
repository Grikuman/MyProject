#include "pch.h"
#include "Audio.h"
#include <iostream>

// シングルトンパターンを実装するための静的メンバ変数
std::unique_ptr<Audio> Audio::m_audio = nullptr;

// データクラスのインスタンスを取得する
Audio* const Audio::GetInstance()
{
    if (m_audio == nullptr)
    {
        m_audio.reset(new Audio());
    }
    return m_audio.get();
}

// コンストラクタ
Audio::Audio()
    : m_system(nullptr), m_sound(nullptr), m_channel(nullptr)
{
    // FMODシステムの初期化
    FMOD::System_Create(&m_system);
}

// 初期化する
void Audio::Initialize()
{
    // FMODシステムの初期化（最大512チャネル、通常モード）
    m_system->init(512, FMOD_INIT_NORMAL, nullptr);
}

// サウンドを再生する
void Audio::PlaySound(const char* filename)
{
    // サウンドの読み込み
    m_system->createSound(filename, FMOD_DEFAULT, nullptr, &m_sound);

    // 音の再生
    m_system->playSound(m_sound, nullptr, false, &m_channel);
}

// 更新する
void Audio::Update()
{
    // FMODの更新処理
    m_system->update();
}

// 終了処理
void Audio::Finalize()
{
    if (m_sound)
    {
        m_sound->release();
    }
    m_system->close();
    m_system->release();
}
