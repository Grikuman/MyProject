/*
	ファイル名：PlayerRunning.h
	　　　概要：プレイヤーの走る状態を管理するクラス
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
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 走る処理
	void Running();
	// 待機状態への移行処理
	void TransitionToIdling();
	// 回避状態への移行処理
	void TransitionToRolling();
	// 向きの処理
	void Direction();

private:
	// プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerRunningAnimation> m_animation;
};
