/*
	ファイル名：PlayerAttackingNormal.h
	　　　概要：プレイヤーの通常攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerAttackingNormalAnimation.h"

// 前方宣言
class Player;

class PlayerAttackingNormal : public IPlayerState
{
public:
	// 攻撃範囲を取得する
	DirectX::BoundingSphere GetAttackRange();

public:
	// コンストラクタ
	PlayerAttackingNormal(Player* player);
	// デストラクタ
	~PlayerAttackingNormal() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 待機状態への移行処理
	void TransitionToIdling();

private:
	// 攻撃の距離
	const float ATTACK_DISTANCE = 3.0f;

private:
	//プレイヤー
	Player* m_player;
	// アニメーション
	std::unique_ptr<PlayerAttackingNormalAnimation> m_animation;
};
