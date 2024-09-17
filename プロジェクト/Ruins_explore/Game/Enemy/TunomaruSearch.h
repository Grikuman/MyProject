/*
	ファイル: TunomaruSearch.h
	クラス  : つのまるサーチクラス
*/
#pragma once
#include "IEnemyState.h"

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
	// つのまる
	Tunomaru* m_tunomaru;
	// モデル
	DirectX::Model* m_model;
};
