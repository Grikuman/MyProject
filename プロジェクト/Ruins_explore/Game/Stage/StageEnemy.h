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
    std::vector<std::unique_ptr<IEnemy>> m_enemies;  // �G�̃��X�g
    bool m_isChangeScene;  // �V�[���J�ڃt���O
};

#endif // ENEMY_SPAWNER_H
