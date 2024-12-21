/*
    �t�@�C�����FStageEnemy.h
    �@�@�@�T�v�F�X�e�[�W�̓G���Ǘ�����N���X
*/
#pragma once
#include <string>
#include <vector>
#include "Game/Player/Player.h"
#include "Game/Interface/IEnemy.h"
#include "Game/Factory/EnemyFactory.h"

class StageEnemy
{
public:
    // �X�e�[�W�J�ڃt���O�̎擾
    bool IsChangeStage() const { return m_isChangeStage; };

public:
    // �R���X�g���N�^
    StageEnemy(Player* player);
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
    // �v���C���[
    Player* m_player;
    // �G�̃��X�g
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    // �X�e�[�W�J�ڃt���O
    bool m_isChangeStage;
};
