/*
	ファイル名：DemonWalking.h
	　　　概要：ウォーロックの歩き状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Demon/Animations/DemonWalkingAnimation.h"

// 前方宣言
class Demon;

class DemonWalking : public IEnemyState
{
public:
	// コンストラクタ
	DemonWalking(Demon* demon);
	// デストラクタ
	~DemonWalking() override; 
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 歩きの処理
	void Walking();
	// パンチ攻撃状態への移行処理
	void TransitionToPunching();

private:
	// 移動速度の補正
	const float APPLY_VELOCITY = 0.04f;
	// パンチ状態に移行する判定距離
	const float PUNCHING_DISTANCE = 5.0f;

private:
	// ウォーロック
	Demon* m_demon;
	// アニメーション
	std::unique_ptr<DemonWalkingAnimation> m_animation;
};
