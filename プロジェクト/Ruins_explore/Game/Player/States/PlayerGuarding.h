/*
	ファイル名：PlayerGuarding.h
	　　　概要：プレイヤーのガード状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerGuardingAnimation.h"

// 前方宣言
class Player;

class PlayerGuarding : public IPlayerState
{
public:
	// コンストラクタ
	PlayerGuarding();
	// デストラクタ
	~PlayerGuarding() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 待機状態への移行処理
	void TransitionToIdling();

private:
	//プレイヤーのポインタ
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerGuardingAnimation> m_animation;
};
