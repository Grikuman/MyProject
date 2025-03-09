#include "pch.h"
#include "Audio.h"
#include <iostream>

// �V���O���g���p�^�[�����������邽�߂̐ÓI�����o�ϐ�
std::unique_ptr<Audio> Audio::m_audio = nullptr;

// �f�[�^�N���X�̃C���X�^���X���擾����
Audio* const Audio::GetInstance()
{
    if (m_audio == nullptr)
    {
        m_audio.reset(new Audio());
    }
    return m_audio.get();
}

// �R���X�g���N�^
Audio::Audio()
    : m_system(nullptr), m_sound(nullptr), m_channel(nullptr)
{
    // FMOD�V�X�e���̏�����
    FMOD::System_Create(&m_system);
}

// ����������
void Audio::Initialize()
{
    // FMOD�V�X�e���̏������i�ő�512�`���l���A�ʏ탂�[�h�j
    m_system->init(512, FMOD_INIT_NORMAL, nullptr);
}

// �T�E���h���Đ�����
void Audio::PlaySound(const char* filename)
{
    // �T�E���h�̓ǂݍ���
    m_system->createSound(filename, FMOD_DEFAULT, nullptr, &m_sound);

    // ���̍Đ�
    m_system->playSound(m_sound, nullptr, false, &m_channel);
}

// �X�V����
void Audio::Update()
{
    // FMOD�̍X�V����
    m_system->update();
}

// �I������
void Audio::Finalize()
{
    if (m_sound)
    {
        m_sound->release();
    }
    m_system->close();
    m_system->release();
}
