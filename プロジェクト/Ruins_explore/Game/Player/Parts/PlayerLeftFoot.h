/*
	ファイル: PlayerLeftFoot.h
	クラス  : プレイヤークラス
*/
#pragma once
#include "IPlayerPart.h"

// 前方宣言
class Player;

class PlayerLeftFoot : public IPlayerPart
{
public:
	// コンストラクタ
	PlayerLeftFoot(Player* player);
	// デストラクタ
	~PlayerLeftFoot();

	// 初期化する
	void Initialize()  override;
	// 更新する
	void Update()      override;
	// 描画する
	void Render()      override;
	// 後処理する
	void Finalize()    override;

	// モデル
	DirectX::Model* m_model;
	// プレイヤー
	Player* m_player;
};
