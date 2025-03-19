/*
	ファイル名：PlayerWalk.h
	　　　概要：プレイヤーの歩行状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// 前方宣言
class Player;

class PlayerWalk : public IPlayerState
{
public:
	// コンストラクタ
	PlayerWalk(Player* player);
	// デストラクタ
	~PlayerWalk() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// プレイヤー移動
	void PlayerMove();
	// 歩行からダッシュへ
	void WalkToDash();
	// 歩行から攻撃へ
	void WalkToAttack();

private:
	// 回転する速さ
	const float ROTATE_SPEED = 3.0f;

private:
	//プレイヤー
	Player* m_player;
	// キーを押している時間
	float m_keyHoldTime;
	// マウスの移動保存
	int m_prevMouse;
};
