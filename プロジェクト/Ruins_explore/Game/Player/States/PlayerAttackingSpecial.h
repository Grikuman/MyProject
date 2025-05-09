/*
	ファイル名：PlayerAttackingSpecial.h
	　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// 前方宣言
class Player;

class PlayerAttackingSpecial : public IPlayerState
{
public:
	// 攻撃範囲を取得する
	DirectX::BoundingSphere GetAttackRange();

public:
	// コンストラクタ
	PlayerAttackingSpecial(Player* player);
	// デストラクタ
	~PlayerAttackingSpecial() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	//プレイヤー
	Player* m_player;
};
