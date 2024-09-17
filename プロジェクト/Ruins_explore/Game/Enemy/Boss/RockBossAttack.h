/*
	ファイル: RockBossAttck.h
	クラス  : 岩ボスアタッククラス
*/
#pragma once
#include "Game/Enemy/IEnemyState.h"

// 前方宣言
class RockBoss;

namespace NRLib
{
	class TPS_Camera;
};

class RockBossAttack : public IEnemyState
{
public:
	// コンストラクタ
	RockBossAttack(RockBoss* RockBoss);
	// デストラクタ
	~RockBossAttack();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

public:
	// 攻撃のバウンディングスフィアを取得する
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	// 攻撃を受けないバウンディングスフィアを取得する
	DirectX::BoundingSphere GetNoDamageBoundingSphere() const;
private:
	// 岩ボス
	RockBoss* m_rockBoss;
	// モデル
	DirectX::Model* m_model;

	// 攻撃までの猶予時間
	float m_atackStartTime;
	const float ATACKSTART_TIME = 60.f;
	// 回転カウント
	float m_rotateCnt;
};
