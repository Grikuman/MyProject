/*
	ファイル名：PlayerGuarding.h
	　　　概要：プレイヤーの歩行状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// 前方宣言
class Player;

class PlayerGuarding : public IPlayerState
{
public:
	// コンストラクタ
	PlayerGuarding(Player* player);
	// デストラクタ
	~PlayerGuarding() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	//プレイヤー
	Player* m_player;
};
