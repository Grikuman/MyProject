/*
	ファイル名：ChargePunch.h
	　　　概要：プレイヤーの溜めパンチを管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerAction.h"

class Player;

class PlayerChargePunch : public IPlayerAction
{
public:
	// 行動を終了するかどうか
	bool IsEndAction() const override { return m_isEndAction; }
public:
	// コンストラクタ
	PlayerChargePunch(Player* player);
	// デストラクタ
	~PlayerChargePunch() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 行動時間をカウントする
	void CountActionTime();

private:
	// 行動時間
	const float ACTION_TIME = 90;

private:
	// プレイヤー
	Player* m_player;
	// 行動カウント
	float m_actionTime;
	// 行動を終了するかどうか
	bool m_isEndAction;
};
