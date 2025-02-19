/*
	ファイル名：NeedleBossAttack.h
	　　　概要：岩ボスの攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class NeedleBoss;;

namespace NRLib
{
	class TPS_Camera;
};

class NeedleBossAttack : public IEnemyState
{
public:
	// 攻撃のバウンディングスフィアを取得する
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	// 攻撃を受けないバウンディングスフィアを取得する
	DirectX::BoundingSphere GetNoDamageBoundingSphere() const;

public:
	// コンストラクタ
	NeedleBossAttack(NeedleBoss* needleBoss);
	// デストラクタ
	~NeedleBossAttack();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();
private:
	// 攻撃開始までの時間
	const float ATACKSTART_TIME = 60.f;

	// 回転攻撃
	void SpinningAttack();

private:
	// 岩ボス
	NeedleBoss* m_needleBoss;
	// モデル
	DirectX::Model* m_model;

	// 攻撃までの猶予時間
	float m_atackStartTime;
	// 回転カウント
	float m_rotateCnt;
};
