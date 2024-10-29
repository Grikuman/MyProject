/*
	ファイル: TunomaruAttack.h
	クラス  : つのまるアタッククラス
*/
#pragma once
#include "IEnemyState.h"

// 前方宣言
class Tunomaru;

class TunomaruAttack : public IEnemyState
{
public:
	// コンストラクタ
	TunomaruAttack(Tunomaru* tunomaru);
	// デストラクタ
	~TunomaruAttack();
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

	// 突進時間
	float m_rushTime;
	// 
	const float MAX_RUSHTIME = 120.f;
};
