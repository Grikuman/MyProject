/*
	ファイル名：MutantWalking.h
	　　　概要：ミュータントの歩き状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantWalkingAnimation.h"

// 前方宣言
class Mutant;
class Player;

class MutantWalking : public IEnemyState
{
public:
	// コンストラクタ
	MutantWalking();
	// デストラクタ
	~MutantWalking() override; 
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
	// 探索から攻撃へ
	void TransitionToRushing();
	// 斬りつけ攻撃状態への移行処理
	void TransitionToSlashing();

private:
	// 速度の補正
	const float APPLY_VELOCITY = 0.08f;
	// 突進状態に移行する判定距離
	const float RUSHING_DISTANCE = 10.0f;
	// 斬りつけ状態に移行する判定距離
	const float SLASHING_DISTANCE = 5.0f;

private:
	// ミュータントのポインタ
	Mutant* m_mutant;
	// アニメーション
	std::unique_ptr<MutantWalkingAnimation> m_animation;
	// プレイヤーのポインタ
	Player* m_player;
};
