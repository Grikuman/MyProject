/*
	ファイル: PlayerIdling.h
	クラス  : プレイヤーアイドリングクラス
*/
#pragma once
#include "IState.h"

// 前方宣言
class Player;

class PlayerIdling : public IState
{
public:
	// コンストラクタ
	PlayerIdling(Player* player);
	// デストラクタ
	~PlayerIdling();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	//プレイヤー
	Player* m_player;
	// モデル
	DirectX::Model* m_model;
};
