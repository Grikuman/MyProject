/*
	ファイル名：PlayerIdling.h
	　　　概要：プレイヤーの歩行状態を管理するクラス
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
	PlayerIdling(Player* player);
	// デストラクタ
	~PlayerIdling() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 待機処理
	void Idling();
	// 走る状態への移行処理
	void TransitionToRunning();
	// 通常攻撃状態への移行処理
	void TransitionToAttackingNormal();

private:
	//プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerIdlingAnimation> m_animation;
};
