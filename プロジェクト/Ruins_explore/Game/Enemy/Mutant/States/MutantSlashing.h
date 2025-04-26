/*
	ファイル名：MutantSlashing.h
	　　　概要：ミュータントの斬りつけ状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantSlashingAnimation.h"

// 前方宣言
class Mutant;

namespace NRLib
{
	class TPS_Camera;
};

class MutantSlashing : public IEnemyState
{
public:
	// 攻撃のバウンディングスフィアを取得する
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	
public:
	// コンストラクタ
	MutantSlashing(Mutant* mutant);
	// デストラクタ
	~MutantSlashing() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 斬りつけ攻撃の処理
	void Slashing();
	// 歩き状態への移行処理
	void TransitionToWalking();

private:
	// ミュータント
	Mutant* m_mutant;
	// アニメーション
	std::unique_ptr<MutantSlashingAnimation> m_animation;
};
