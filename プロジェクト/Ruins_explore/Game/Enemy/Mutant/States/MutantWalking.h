/*
	ファイル名：MutantWalking.h
	　　　概要：ミュータントの歩き状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantWalkingAnimation.h"

// 前方宣言
class Mutant;

class MutantWalking : public IEnemyState
{
public:
	// コンストラクタ
	MutantWalking(Mutant* mutant);
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
	// ミュータント
	Mutant* m_mutant;
	// アニメーション
	std::unique_ptr<MutantWalkingAnimation> m_animation;
};
