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
	// 攻撃範囲を取得
	DirectX::BoundingSphere GetAttackRange() const override; 

public:
	// 行動を強制終了させる
	void EndAction() { m_actionTime = 0; }

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
	// 移動させる
	void Move();

private:
	// 行動時間
	const float ACTION_TIME = 60;

private:
	// プレイヤー
	Player* m_player;
	// 行動カウント
	float m_actionTime;
	// 行動を終了するかどうか
	bool m_isEndAction;
};
