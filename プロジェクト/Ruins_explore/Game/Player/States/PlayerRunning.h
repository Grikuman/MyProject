/*
	ファイル名：PlayerRunning.h
	　　　概要：プレイヤーの走り状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerRunningAnimation.h"

// 前方宣言
class Player;

class PlayerRunning : public IPlayerState
{
public:
	// コンストラクタ
	PlayerRunning(Player* player);
	// デストラクタ
	~PlayerRunning() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 走る処理
	void Running();
	// 待機状態への移行処理
	void TransitionToIdling();
	// 回避状態への移行処理
	void TransitionToRolling();
	// 通常攻撃状態への移行処理
	void TransitionToAttackingNormal();
	// 向きの処理
	void Direction();

private:
	// プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerRunningAnimation> m_animation;
};
