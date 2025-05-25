/*
	ファイル名：MutantSlashing.h
	　　　概要：ミュータントの斬りつけ状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Mutant/Animations/MutantSlashingAnimation.h"

// 前方宣言
class Mutant;
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class MutantSlashing : public IEnemyState
{
public:
	// コンストラクタ
	MutantSlashing();
	// デストラクタ
	~MutantSlashing() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 斬りつけ攻撃の処理
	void Slashing();
	// 歩き状態への移行処理
	void TransitionToJumping();

private:
	// 攻撃の当たる距離
	const float ATTACK_DISTANCE = 5.0f;
	// 攻撃の当たる判定範囲
	const float ATTACK_DOT = 0.5f;
	// 攻撃が当たった際のカメラ振動の強度
	const float CAMERA_INTENSITY = 0.2f;
	// 攻撃が当たった際のカメラ振動の時間
	const float CAMERA_DURATION = 0.4f;

private:
	// ミュータント
	Mutant* m_mutant;
	// アニメーション
	std::unique_ptr<MutantSlashingAnimation> m_animation;
	// プレイヤーのポインタ
	Player* m_player;
};
