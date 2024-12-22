/*
	ファイル名：PlayerLeftHand.h
	　　　概要：プレイヤーの左手を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// 前方宣言
class Player;

class PlayerLeftHand : public IPlayerPart
{
public:
	// コンストラクタ
	PlayerLeftHand(Player* player);
	// デストラクタ
	~PlayerLeftHand();

	// 初期化する
	void Initialize()  override;
	// 更新する
	void Update()      override;
	// 描画する
	void Render()      override;
	// 後処理する
	void Finalize()    override;
private:
	// 手の位置の定数
	const DirectX::SimpleMath::Vector3 m_nonePosition  = DirectX::SimpleMath::Vector3(-1.4f, 0.8f, 0.0f);
	const DirectX::SimpleMath::Vector3 m_punchPosition = DirectX::SimpleMath::Vector3(-1.4f, 0.8f, 1.0f);

private:
	// モデル
	DirectX::Model* m_model;
	// プレイヤー
	Player* m_player;
	// 現在の手の位置
	DirectX::SimpleMath::Vector3 m_currentHandPosition;
};
