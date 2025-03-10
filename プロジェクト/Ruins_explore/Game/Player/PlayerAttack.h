/*
	ファイル名：PlayerAttack.h
	　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Interface/IPlayerAction.h"
#include "Game/Player/Action/PlayerNormalPunch.h"
#include "Game/Player/Action/PlayerChargePunch.h"

// 前方宣言
class Player;
class SwordEffect;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerAttack : public IPlayerState
{
public:
	// 攻撃行動を変更する
	void ChangeAttackAction(IPlayerAction* playerAction) { m_currentAttackAction = playerAction;  }

public:
	// 現在の攻撃行動を取得する
	IPlayerAction* GetCurrentAttackAction() const   { return m_currentAttackAction; }
	// プレイヤー通常パンチを取得する
	PlayerNormalPunch* GetPlayerNormalPunch() const { return m_normalPunch.get(); }
	// プレイヤーチャージパンチを取得する
	PlayerChargePunch* GetPlayerChargePunch() const { return m_chargePunch.get(); }
	// 攻撃範囲を取得する
	DirectX::BoundingSphere GetAttackRange();

public:
	// コンストラクタ
	PlayerAttack(Player* player);
	// デストラクタ
	~PlayerAttack() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 攻撃から歩行へ
	void AttackToWalk();

private:
	//プレイヤー
	Player* m_player;
	// 現在の攻撃行動
	IPlayerAction* m_currentAttackAction;
	// 通常パンチ
	std::unique_ptr<PlayerNormalPunch> m_normalPunch;
	// 溜めパンチ
	std::unique_ptr<PlayerChargePunch> m_chargePunch;
	// カウント
	int m_cnt;
};
