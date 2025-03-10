/*
	ファイル名：TunomaruKnockback.h
	　　　概要：つのまるの吹っ飛び状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class Tunomaru;

class TunomaruKnockback : public IEnemyState
{
public:
	// コンストラクタ
	TunomaruKnockback(Tunomaru* tunomaru);
	// デストラクタ
	~TunomaruKnockback() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;
private:
	// 突進時間
	const float MAX_KNOCKBACK_TIME = 120.0f;

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// 突進時間
	float m_knockbackTime;
};
