#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <string>
#include <vector>
#include "Game/Player/Player.h"
#include "Game/Interface/IEnemy.h"
#include "Game/Factory/EnemyFactory.h"

class StageEnemy 
{
public:
    // �V�[���J�ڃt���O�̎擾
    bool IsChangeScene() const;

public:
    // �R���X�g���N�^
    StageEnemy(Player* player);

    ~StageEnemy();

    // ����������
    void Initialize(const std::string& stageName);

    // �X�V����
    void Update();

    // �`�揈��
    void Render();

    // ��n��
    void Finalize();

private:
    // �v���C���[
    Player* m_player;
    // �G�̃��X�g
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    // �V�[���J�ڃt���O
    bool m_isChangeScene;
};

#endif // ENEMY_SPAWNER_H
