/*
	ファイル: Player.h
	クラス  : プレイヤークラス
*/
#pragma once
#include "IState.h"
#include "PlayerIdling.h"
#include "PlayerAttack.h"
#include "PlayerDash.h"

#include "Game/UI/PlayerUIManager.h"
#include "Game/Effect/PlayerEffectManager.h"

// 前方宣言

namespace NRLib
{
	class TPS_Camera;
};

class Player
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(float elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();
public:
	// プレイヤーアイドリングを取得する
	PlayerIdling* GetPlayerIdling() { return m_playerIdling.get(); }
	// プレイヤーアタックを取得する
	PlayerAttack* GetPlayerAttack() { return m_playerAttack.get(); }
	// プレイヤーダッシュを取得する
	PlayerDash* GetPlayerDash() { return m_playerDash.get(); }

public:
	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 速度を取得する
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// 角度を取得する
	float GetAngle() const { return m_playerAngle; }
	// 体力を取得する
	int GetHP() const { return m_hp; }
	// 最大体力を取得する
	int GetMAXHP() const { return MAX_HP; }
	// スタミナを取得する
	int GetStamina() const { return m_stamina; }
	// 最大スタミナを取得する
	int GetMAXSTAMINA() const { return MAX_STAMINA; }
	// 無敵を取得
	bool GetInvincible() const { return m_invincible; }

	// 攻撃しているか取得する
	bool GetIsAttack();
	// バウンディングスフィアを取得する
	DirectX::BoundingSphere GetBoundingSphere();

	// カメラを取得する
	NRLib::TPS_Camera* GetCamera();

public:
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// 角度を設定する
	void SetAngle(const float angle) { m_playerAngle = angle; }
	// 体力を設定する
	void SetHP(const int hp) { m_hp = hp; }
	// スタミナを設定する
	void SetStamina(const int stamina) { m_stamina = stamina; }
	//無敵を設定する
	void SetInvincible(const bool invincible) { m_invincible = invincible; }

	// ステートを変更する
	void ChangeState(IState* newState);
private:
	// UI管理クラス
	std::unique_ptr<PlayerUIManager> m_playerUIManager;
	// エフェクト管理クラス
	std::unique_ptr<PlayerEffectManager> m_playerEffectManager;
	// 現在のステート
	IState* m_currentState;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// モデル
	DirectX::Model* m_model;

	// アイドリング状態
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// アタック状態
	std::unique_ptr<PlayerAttack> m_playerAttack;
	// ダッシュ状態
	std::unique_ptr<PlayerDash> m_playerDash;

	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 角度
	float m_playerAngle;
	// 体力
	int m_hp;
	// 最大体力
	const int MAX_HP = 6;
	// スタミナ
	int m_stamina;
	// 最大スタミナ
	const int MAX_STAMINA = 6;
	// スタミナの回復カウント
	float m_chargeCnt;
	// 無敵
	bool m_invincible;
	// 無敵時間
	float m_invincibleTime;
};
