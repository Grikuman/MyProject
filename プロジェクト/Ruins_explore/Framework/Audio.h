#pragma once
#include "fmod.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class Audio
{
public:
    // �C���X�^���X�擾�i�V���O���g���j
    static Audio* const GetInstance();

public:
    ~Audio() = default;

    // ������
    void Initialize();
    // �X�V
    void Update();
    // �I������
    void Finalize();

    // BGM��SE�̍Đ�
    void PlayBGM(const std::string& name, float volume);
    void PlaySE(const std::string& name);
    // BGM�̉��ʂ�ݒ肷��
    void SetBGMVolume(float volume) { m_bgmChannel->setVolume(volume); }
    // BGM���~����
    void StopBGM();

private:
    // BGM��SE�̓ǂݍ���
    void LoadBGM(const std::string& name, const char* filename);
    void LoadSE(const std::string& name, const char* filename);

private:
    // �R���X�g���N�^
    Audio();

    // �R�s�[�E���[�u�֎~
    void operator=(const Audio&) = delete;
    Audio& operator=(Audio&&) = delete;
    Audio(const Audio&) = delete;
    Audio(Audio&&) = delete;

private:
    static std::unique_ptr<Audio> m_audio;

    // FMOD�̃V�X�e��
    FMOD::System* m_system;
    // BGM��SE�̊Ǘ�
    std::unordered_map<std::string, FMOD::Sound*> m_bgm;
    std::unordered_map<std::string, FMOD::Sound*> m_se;
    // BGM��SE�̃`�����l��
    FMOD::Channel* m_bgmChannel;
    FMOD::Channel* m_seChannel;
};
