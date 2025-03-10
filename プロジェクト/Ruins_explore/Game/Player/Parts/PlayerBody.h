/*
	ファイル名：PlayerBody.h
	　　　概要：プレイヤーの体を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// 前方宣言
class Player;

class PlayerBody : public IPlayerPart
{
public:
	// コンストラクタ
	PlayerBody(Player* player);
	// デストラクタ
	~PlayerBody();

	// 初期化する
	void Initialize()override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	// プレイヤー
	Player* m_player;
};
