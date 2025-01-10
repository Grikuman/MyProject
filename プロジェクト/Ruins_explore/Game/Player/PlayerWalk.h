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
	~PlayerWalk();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();
private:
	// プレイヤー移動
	void PlayerMove();
	// 歩行からダッシュへ
	void WalkToDash();
	// 歩行から攻撃へ
	void WalkToAttack();
	// 歩行からジャンプへ
	void WalkToJump();

private:
	//プレイヤー
	Player* m_player;
	// モデル
	DirectX::Model* m_model;
	// キーを押している時間
	float m_keyHoldTime;
};
