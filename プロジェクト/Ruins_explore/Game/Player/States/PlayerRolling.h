/*
	ファイル名：PlayerRolling.h
	　　　概要：プレイヤーの回避状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerRollingAnimation.h"

// 前方宣言
class Player;

class PlayerRolling : public IPlayerState
{
public:
	// コンストラクタ
	PlayerRolling(Player* player);
	// デストラクタ
	~PlayerRolling() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 回避処理
	void Rolling();
	// 待機状態への移行処理
	void TransitionToIdling();

private:
	// 速度の補正
	const float APPLY_VELOCITY = 0.1f;

private:
	//プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerRollingAnimation> m_animation;
};
