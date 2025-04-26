/*
	ファイル名：MutantRushing.h
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantRushingAnimation.h"

// 前方宣言
class Mutant;;

namespace NRLib
{
	class TPS_Camera;
};

class MutantRushing : public IEnemyState
{
public:
	// 攻撃のバウンディングスフィアを取得する
	DirectX::BoundingSphere GetAttackBoundingSphere() const;

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
	// ミュータント
	Mutant* m_mutant;
	// アニメーション
	std::unique_ptr<MutantRushingAnimation> m_animation;
};
