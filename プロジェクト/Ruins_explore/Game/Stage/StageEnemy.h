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
    // シーン遷移フラグの取得
    bool IsChangeScene() const;

public:
    // コンストラクタ
    StageEnemy(Player* player);

    ~StageEnemy();

    // 初期化処理
    void Initialize(const std::string& stageName);

    // 更新処理
    void Update();

    // 描画処理
    void Render();

    // 後始末
    void Finalize();

private:
    // プレイヤー
    Player* m_player;
    // 敵のリスト
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    // シーン遷移フラグ
    bool m_isChangeScene;
};

#endif // ENEMY_SPAWNER_H
