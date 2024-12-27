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
	// 攻撃範囲を取得
	DirectX::BoundingSphere GetAttackRange();

public:
	// プレイヤー通常パンチを取得する
	PlayerNormalPunch* GetPlayerNormalPunch() const { return m_normalPunch.get(); }
	// プレイヤー通常パンチを取得する
	PlayerChargePunch* GetPlayerChargePunch() const { return m_chargePunch.get(); }

public:
	// コンストラクタ
	PlayerAttack(Player* player);
	// デストラクタ
	~PlayerAttack();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

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
	// モデル
	DirectX::Model* m_model;
	// 斬撃エフェクト
	std::unique_ptr<SwordEffect> m_swordEffect;
	
	// カウント
	int m_cnt;
};
