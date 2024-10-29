/*
	ファイル: EnemySpawner.h
	クラス  : 敵生成クラス
*/
#pragma once
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"

// 前方宣言
class Player;
class EnemyUIManager;

namespace NRLib
{
	class TPS_Camera;
}

// 一般的なシーンクラス
class EnemySpawner
{
public:
	EnemySpawner(Player* player);
	~EnemySpawner();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 終了処理
	void Finalize();
	// シーン変更する
	bool IsChangeScene();
private:
	// プレイヤー
	Player* m_player;
	// 敵の最大数
	const int MAX_ENEMY = 2;
	// それぞれの敵の数
	static const int MAX_TUNOMARU = 2;
	// つのまる
	std::unique_ptr<Tunomaru> m_tunomaru[MAX_TUNOMARU];
	// 岩ボス
	std::unique_ptr<RockBoss> m_rockBoss;
	// 敵のUI管理クラス
	std::unique_ptr<EnemyUIManager> m_enemyUIManager;

	// 生存している敵の数
	int m_aliveEnemy;
	// シーン遷移フラグ
	bool m_isChangeScene;
};
