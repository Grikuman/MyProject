/*
    ファイル名：StageEnemy.h
    　　　概要：ステージの敵を管理するクラス
*/
#pragma once
#include <string>
#include <vector>
#include "Game/Interface/IEnemy.h"

class StageEnemy
{
public:
    // ステージ遷移フラグの取得
    bool IsChangeStage() const { return m_isChangeStage; };
    // 全ての敵を取得する
    std::vector<std::unique_ptr<IEnemy>>& GetEnemies() { return m_enemies; }

public:
    // コンストラクタ
    StageEnemy();
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
    // ファイルを読み込む
    void LoadFile(const std::string& stageName);

private:
    // 敵のリスト
    std::vector<std::unique_ptr<IEnemy>> m_enemies;
    // ステージ遷移フラグ
    bool m_isChangeStage;
};
