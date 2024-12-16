/*
	ファイル: TunomaruAttack.h
	クラス  : つのまるアタッククラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

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
	// 後処理する
	void Finalize();
private:
	// 突進時間
	const float MAX_RUSHTIME = 120.f;

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// モデル
	DirectX::Model* m_model;

	// 突進時間
	float m_rushTime;
};
