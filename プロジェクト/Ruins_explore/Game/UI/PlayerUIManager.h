/*
	@file	PlayerUIManager.h
	@brief	プレイヤーのUIを管理するクラス
*/
#pragma once
#include "PlayerStatusUI.h"

// 前方宣言
class Player;

class PlayerUIManager
{
public:
	// コンストラクタ
	PlayerUIManager(Player* player);
	// デストラクタ
	~PlayerUIManager();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();
private:
	// Player
	Player* m_player;
	// HPUIクラス
	std::unique_ptr<PlayerStatusUI> m_playerStatusUI;
};
