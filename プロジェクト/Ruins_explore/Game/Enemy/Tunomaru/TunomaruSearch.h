/*
	ファイル名：TunomaruSearch.h
	　　　概要：つのまるの索敵状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class Tunomaru;

class TunomaruSearch : public IEnemyState
{
public:
	// コンストラクタ
	TunomaruSearch(Tunomaru* tunomaru);
	// デストラクタ
	~TunomaruSearch();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// プレイヤーを追いかける
	void ChasePlayer();
	// 探索から攻撃へ
	void SearchToAttack();

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// モデル
	DirectX::Model* m_model;
};
