/*
	ファイル: RockBossSearch.h
	クラス  : 岩ボスサーチクラス
*/
#pragma once
#include "Game/Enemy/IEnemyState.h"

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
	RockBossSearch(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model);
	// デストラクタ
	~RockBossSearch();
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
	const std::unique_ptr<DirectX::Model>& m_model;
};
