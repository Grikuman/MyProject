/*
	ファイル名：NeedleBossSearch.h
	　　　概要：岩ボスの探索状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class CommonResources;
class NeedleBoss;

namespace NRLib
{
	class TPS_Camera;
};

class NeedleBossSearch : public IEnemyState
{
public:
	// コンストラクタ
	NeedleBossSearch(NeedleBoss* needleBoss);
	// デストラクタ
	~NeedleBossSearch();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 後処理する
	void Finalize();

private:
	// 探索から攻撃へ
	void SearchToAttack();

private:
	// 岩ボス
	NeedleBoss* m_needleBoss;
	// モデル
	DirectX::Model* m_model;
};
