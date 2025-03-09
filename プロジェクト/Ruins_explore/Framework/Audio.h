#pragma once
#include "fmod.hpp"

class Audio
{
public:
    // コリジョンのインスタンス取得
    static Audio* const GetInstance();

public:
    // デストラクタ
    ~Audio() = default;
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 終了処理
    void Finalize();

    // サウンドを再生する
    void PlaySound(const char* filename);

private:
    // コンストラクタ
    Audio();

    // インスタンスをコピーすることを禁止する
    void operator=(const Audio&) = delete;

    // インスタンスをムーブすることを禁止する
    Audio& operator= (Audio&&) = delete;
    // コピーコンストラクタは禁止する
    Audio(const Audio&) = delete;
    // ムーブコンストラクタは禁止する
    Audio(Audio&&) = delete;

private:
    // シングルトン
    static std::unique_ptr<Audio> m_audio;

    // FMODのシステム
    FMOD::System* m_system;
    // FMODのサウンド
    FMOD::Sound* m_sound;
    // FMODのチャンネル
    FMOD::Channel* m_channel;
};
