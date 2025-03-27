/*
	ファイル名：PlayerRolling.h
	　　　概要：プレイヤーのダッシュ状態を管理するクラス
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
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 回避処理
	void Rolling();
	// 待機状態への移行処理
	void TransitionToIdling();

private:
	//プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerRollingAnimation> m_animation;
};
