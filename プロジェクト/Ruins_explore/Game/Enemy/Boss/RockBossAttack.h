/*
	ファイル名：RockBossAttack.h
	　　　概要：岩ボスの攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class RockBoss;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossAttack : public IEnemyState
{
public:
	// 攻撃のバウンディングスフィアを取得する
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	// 攻撃を受けないバウンディングスフィアを取得する
	DirectX::BoundingSphere GetNoDamageBoundingSphere() const;

public:
	// コンストラクタ
	RockBossAttack(RockBoss* RockBoss);
	// デストラクタ
	~RockBossAttack();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 後処理する
	void Finalize();
private:
	// 攻撃開始までの時間
	const float ATACKSTART_TIME = 60.f;

	// 回転攻撃
	void SpinningAttack();

private:
	// 岩ボス
	RockBoss* m_rockBoss;
	// モデル
	DirectX::Model* m_model;

	// 攻撃までの猶予時間
	float m_atackStartTime;
	// 回転カウント
	float m_rotateCnt;
};
