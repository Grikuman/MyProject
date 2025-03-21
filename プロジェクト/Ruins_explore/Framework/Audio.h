#pragma once
#include "fmod.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class Audio
{
public:
    // インスタンス取得（シングルトン）
    static Audio* const GetInstance();

public:
    ~Audio() = default;

    // 初期化
    void Initialize();
    // 更新
    void Update();
    // 終了処理
    void Finalize();

    // BGMとSEの再生
    void PlayBGM(const std::string& name, float volume);
    void PlaySE(const std::string& name);
    // BGMの音量を設定する
    void SetBGMVolume(float volume) { m_bgmChannel->setVolume(volume); }
    // BGMを停止する
    void StopBGM();

private:
    // BGMとSEの読み込み
    void LoadBGM(const std::string& name, const char* filename);
    void LoadSE(const std::string& name, const char* filename);

private:
    // コンストラクタ
    Audio();

    // コピー・ムーブ禁止
    void operator=(const Audio&) = delete;
    Audio& operator=(Audio&&) = delete;
    Audio(const Audio&) = delete;
    Audio(Audio&&) = delete;

private:
    static std::unique_ptr<Audio> m_audio;

    // FMODのシステム
    FMOD::System* m_system;
    // BGMとSEの管理
    std::unordered_map<std::string, FMOD::Sound*> m_bgm;
    std::unordered_map<std::string, FMOD::Sound*> m_se;
    // BGMとSEのチャンネル
    FMOD::Channel* m_bgmChannel;
    FMOD::Channel* m_seChannel;
};
