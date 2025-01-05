/*
	ファイル名：RockBossSearch.h
	　　　概要：岩ボスの探索状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class CommonResources;
class RockBoss;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossSearch : public IEnemyState
{
public:
	// コンストラクタ
	RockBossSearch(RockBoss* RockBoss);
	// デストラクタ
	~RockBossSearch();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 後処理する
	void Finalize();

private:
	void SearchToAttack();

private:
	// 岩ボス
	RockBoss* m_rockBoss;
	// モデル
	DirectX::Model* m_model;
};
