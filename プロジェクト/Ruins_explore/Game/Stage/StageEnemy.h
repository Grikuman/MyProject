/*
    ファイル名：StageEnemy.h
    　　　概要：ステージの敵を管理するクラス
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
    // ステージ遷移フラグの取得
    bool IsChangeStage() const { return m_isChangeStage; };

public:
    // コンストラクタ
    StageEnemy(Player* player);
    // デストラクト
    ~StageEnemy();
    // 初期化処理
    void Initialize(const std::string& stageName);
    // 更新処理
    void Update();
    // 描画処理
    void Render();
    // 終了処理
    void Finalize();

private:
    // プレイヤー
    Player* m_player;
    // 敵のリスト
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    // ステージ遷移フラグ
    bool m_isChangeStage;
};
