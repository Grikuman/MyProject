/*
	ファイル名：RockBossDown.h
	　　　概要：岩ボスのダウン状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

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
	// 後処理する
	void Finalize();
private:
	// 時間
	const float MAX_DOWNTIME = 180.f;

private:
	// 岩ボス
	RockBoss* m_rockBoss;
	// モデル
	DirectX::Model* m_model;

	// ダウン時間
	float m_downTime;
};
