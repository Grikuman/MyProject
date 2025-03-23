/*
	ファイル名：PlayerLeftHand.h
	　　　概要：プレイヤーの左手を管理するクラス
*/
#pragma once

// 前方宣言
class Player;

class PlayerLeftHand
{
public:
	// コンストラクタ
	PlayerLeftHand(Player* player);
	// デストラクタ
	~PlayerLeftHand();

	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// 手の位置
	const DirectX::SimpleMath::Vector3 m_nonePosition  = DirectX::SimpleMath::Vector3(-1.4f, 0.0f, 0.0f);
	const DirectX::SimpleMath::Vector3 m_punchPosition = DirectX::SimpleMath::Vector3(-1.4f, 0.0f, 1.0f);

private:
	// プレイヤー
	Player* m_player;
	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	// 現在の手の位置
	DirectX::SimpleMath::Vector3 m_currentHandPosition;
};
