/*
	ファイル名：PlayerNormalPunch.h
	　　　概要：プレイヤーの通常パンチ管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerAction.h"

class Player;

class PlayerNormalPunch : public IPlayerAction
{
public:
	// 行動を終了するかどうか
	bool IsEndAction() const override { return m_isEndAction; }
	// 攻撃範囲を取得する
	DirectX::BoundingSphere GetAttackRange() const override;

public:
	// コンストラクタ
	PlayerNormalPunch(Player* player);
	// デストラクタ
	~PlayerNormalPunch();
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
	const float ACTION_TIME = 30;

private:
	// プレイヤー
	Player* m_player;
	// 行動カウント
	float m_actionTime;
	// 行動を終了するかどうか
	bool m_isEndAction;
};
