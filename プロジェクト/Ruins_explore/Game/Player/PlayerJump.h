/*
	ファイル名：PlayerJump.h
	　　　概要：プレイヤーのジャンプ状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// 前方宣言
class Player;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerJump : public IPlayerState
{
public:
	// コンストラクタ
	PlayerJump(Player* player);
	// デストラクタ
	~PlayerJump();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// ジャンプ処理
	void Jump();
	// 移動処理
	void Move();
	// ジャンプから歩行へ
	void JumpToWalk();

private:
	// ジャンプを行う時間
	const float JUMP_TIME = 10;

private:
	//プレイヤー
	Player* m_player;
	
	// ジャンプ時間
	float m_jumpTime; 
};
