/*
	ファイル名：WarrokWalking.h
	　　　概要：ウォーロックの歩き状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Warrok/Animations/WarrokWalkingAnimation.h"

// 前方宣言
class Warrok;
class Player;

class WarrokWalking : public IEnemyState
{
public:
	// コンストラクタ
	WarrokWalking();
	// デストラクタ
	~WarrokWalking() override; 
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
	const float APPLY_VELOCITY = 0.08f;
	// パンチ状態に移行する判定距離
	const float PUNCHING_DISTANCE = 5.0f;

private:
	// ウォーロックのポインタ
	Warrok* m_warrok;
	// アニメーション
	std::unique_ptr<WarrokWalkingAnimation> m_animation;
	// プレイヤーのポインタ
	Player* m_player;
};
