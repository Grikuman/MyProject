/*
	ファイル: PlayerRightFoot.h
	クラス  : プレイヤークラス
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// 前方宣言
class Player;

struct MoveLeftFoot
{
	DirectX::SimpleMath::Vector3 first   = DirectX::SimpleMath::Vector3(-1.f, 0.1f, -0.1f);
	DirectX::SimpleMath::Vector3 second  = DirectX::SimpleMath::Vector3(-1.f, 0.1f, 0.0f);
	DirectX::SimpleMath::Vector3 third   = DirectX::SimpleMath::Vector3(-1.f, 0.1f, 0.1f);
	DirectX::SimpleMath::Vector3 forth   = DirectX::SimpleMath::Vector3(-1.f, 0.1f, 0.2f);
};

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

private:
	// 歩行処理
	void Walk();

private:
	// モデル
	DirectX::Model* m_model;
	// プレイヤー
	Player* m_player;

	// 現在の足の位置
	DirectX::SimpleMath::Vector3 m_nowPosition;
	// 移動座標
	MoveLeftFoot m_movePosition;
	// 移動カウント
	int m_moveCount;
	// 進行方向
	bool m_isForward;
};