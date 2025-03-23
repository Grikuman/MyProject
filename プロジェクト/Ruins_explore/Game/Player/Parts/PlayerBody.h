/*
	ファイル名：PlayerBody.h
	　　　概要：プレイヤーの体を管理するクラス
*/
#pragma once
#include "Game/Player/Parts/PlayerLeftHand.h"
#include "Game/Player/Parts/PlayerRightHand.h"

// 前方宣言
class Player;

class PlayerBody
{
public:
	// コンストラクタ
	PlayerBody(Player* player);
	// デストラクタ
	~PlayerBody();

	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// プレイヤー
	Player* m_player;
	// 左手
	std::unique_ptr<PlayerLeftHand> m_leftHand;
	// 右手
	std::unique_ptr<PlayerRightHand> m_rightHand;
	// モデル
	std::unique_ptr<DirectX::Model> m_model;
};
