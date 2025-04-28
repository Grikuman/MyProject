/*
	ファイル名：MutantRushing.h
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantRushingAnimation.h"

// 前方宣言
class Mutant;;

class MutantRushing : public IEnemyState
{
public:
	// コンストラクタ
	MutantRushing(Mutant* mutant);
	// デストラクタ
	~MutantRushing() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;


private:
	// 突進の処理
	void Rushing();
	// 歩き状態への移行処理
	void TransitionToWalking();

private:
	// 速度の補正
	const float APPLY_VELOCITY = 0.15f;
	// 歩き状態に移行する判定距離
	const float WALKING_DISTANCE = 10.0f;

private:
	// ミュータント
	Mutant* m_mutant;
	// アニメーション
	std::unique_ptr<MutantRushingAnimation> m_animation;
};
