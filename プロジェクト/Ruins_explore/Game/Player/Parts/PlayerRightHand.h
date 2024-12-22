/*
	ファイル名：PlayerRightHand.h
	　　　概要：プレイヤーの右手を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// 前方宣言
class Player;

class PlayerRightHand : public IPlayerPart
{
public:
	// コンストラクタ
	PlayerRightHand(Player* player);
	// デストラクタ
	~PlayerRightHand();

	// 初期化する
	void Initialize()  override;
	// 更新する
	void Update()      override;
	// 描画する
	void Render()      override;
	// 後処理する
	void Finalize()    override;

private: 

private:
	// 手の位置の定数
	const DirectX::SimpleMath::Vector3 m_nonePosition  = DirectX::SimpleMath::Vector3(1.4f, 0.8f, 0.0f);
	const DirectX::SimpleMath::Vector3 m_punchPosition = DirectX::SimpleMath::Vector3(1.4f, 0.8f, -2.0f);

private:
	// モデル
	DirectX::Model* m_model;
	// プレイヤー
	Player* m_player;
	// 現在の手の位置
	DirectX::SimpleMath::Vector3 m_currentHandPosition;
};
