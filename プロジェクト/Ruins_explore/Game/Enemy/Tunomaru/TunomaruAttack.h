/*
	ファイル名：TunomaruAttack.h
	　　　概要：つのまるの攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Effect/DebrisEffect.h"

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
	void Rush();

private:
	// 待機時間
	const float MAX_STAYTIME = 30.0f;
	// 突進時間
	const float MAX_RUSHTIME = 120.0f;

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// 破片エフェクト
	std::unique_ptr<DebrisEffect> m_debrisEffect;
	// 待機時間
	float m_stayTime;
	// 突進時間
	float m_rushTime;
};
