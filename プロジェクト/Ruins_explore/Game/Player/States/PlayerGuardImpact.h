/*
	ファイル名：PlayerGuardImpact.h
	　　　概要：プレイヤーのガード状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerGuardImpactAnimation.h"

// 前方宣言
class Player;

class PlayerGuardImpact : public IPlayerState
{
public:
	// コンストラクタ
	PlayerGuardImpact();
	// デストラクタ
	~PlayerGuardImpact() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	//プレイヤーのポインタ
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerGuardImpactAnimation> m_animation;
};
