/*
    �t�@�C�����FStageEnemy.h
    �@�@�@�T�v�F�X�e�[�W�̓G���Ǘ�����N���X
*/
#pragma once
#include <string>
#include <vector>
#include "Game/Interface/IEnemy.h"

class StageEnemy
{
public:
    // �X�e�[�W�J�ڃt���O�̎擾
    bool IsChangeStage() const { return m_isChangeStage; };
    // �S�Ă̓G���擾����
    std::vector<std::unique_ptr<IEnemy>>& GetEnemies() { return m_enemies; }

public:
    // �R���X�g���N�^
    StageEnemy();
    // �f�X�g���N�g
    ~StageEnemy();
    // ����������
    void Initialize(const std::string& stageName);
    // �X�V����
    void Update();
    // �`�揈��
    void Render();
    // �I������
    void Finalize();

private:
    // �t�@�C����ǂݍ���
    void LoadFile(const std::string& stageName);

private:
    // �G�̃��X�g
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    // �X�e�[�W�J�ڃt���O
    bool m_isChangeStage;
};
