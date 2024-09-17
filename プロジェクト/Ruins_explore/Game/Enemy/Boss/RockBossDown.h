/*
	ファイル: RockBossDown.h
	クラス  : 岩ボスダウンクラス
*/
#pragma once
#include "Game/Enemy/IEnemyState.h"

// 前方宣言
class Tunomaru;

class RockBossDown : public IEnemyState
{
public:
	// コンストラクタ
	RockBossDown(RockBoss* RockBoss);
	// デストラクタ
	~RockBossDown();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// 岩ボス
	RockBoss* m_rockBoss;
	// モデル
	DirectX::Model* m_model;

	// ダウン時間
	float m_downTime;
	// 時間
	const float MAX_DOWNTIME = 90.f;
};
