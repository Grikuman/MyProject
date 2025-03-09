#pragma once
#include "fmod.hpp"

class Audio
{
public:
    // �R���W�����̃C���X�^���X�擾
    static Audio* const GetInstance();

public:
    // �f�X�g���N�^
    ~Audio() = default;
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �I������
    void Finalize();

    // �T�E���h���Đ�����
    void PlaySound(const char* filename);

private:
    // �R���X�g���N�^
    Audio();

    // �C���X�^���X���R�s�[���邱�Ƃ��֎~����
    void operator=(const Audio&) = delete;

    // �C���X�^���X�����[�u���邱�Ƃ��֎~����
    Audio& operator= (Audio&&) = delete;
    // �R�s�[�R���X�g���N�^�͋֎~����
    Audio(const Audio&) = delete;
    // ���[�u�R���X�g���N�^�͋֎~����
    Audio(Audio&&) = delete;

private:
    // �V���O���g��
    static std::unique_ptr<Audio> m_audio;

    // FMOD�̃V�X�e��
    FMOD::System* m_system;
    // FMOD�̃T�E���h
    FMOD::Sound* m_sound;
    // FMOD�̃`�����l��
    FMOD::Channel* m_channel;
};
