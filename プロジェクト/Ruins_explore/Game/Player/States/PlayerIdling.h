/*
	ファイル名：PlayerIdling.h
	　　　概要：プレイヤーの待機状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerIdlingAnimation.h"

// 前方宣言
class Player;

class PlayerIdling : public IPlayerState
{
public:
	// コンストラクタ
	PlayerIdling();
	// デストラクタ
	~PlayerIdling() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 待機処理
	void Idling();
	// 走り状態への移行処理
	void TransitionToRunning();
	// 通常攻撃状態への移行処理
	void TransitionToAttackingNormal();

private:
	//プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerIdlingAnimation> m_animation;
};
