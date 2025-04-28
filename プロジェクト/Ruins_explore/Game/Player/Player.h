/*
	ファイル名：Player.h
	　　　概要：プレイヤーの情報を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/States/PlayerIdling.h"
#include "Game/Player/States/PlayerRunning.h"
#include "Game/Player/States/PlayerRolling.h"
#include "Game/Player/States/PlayerAttackingNormal.h"
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
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// 速度を加算する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// 速度に係数をかける
	void ApplyVelocity(float scale) { m_velocity *= scale; }
	// 回転を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle = angle; }
	// 体力を設定する
	void SetHP(const int hp) { m_hp = hp; }
	// スタミナを設定する
	void SetStamina(const int stamina) { m_stamina = stamina; }
	// 無敵を設定する
	void SetInvincible(const bool invincible) { m_invincible = invincible; }
	// 向きを設定する
	void SetDirection(const DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }
	// ステートを変更する
	void ChangeState(IPlayerState* newState) { m_currentState = newState; }

public:
	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 速度を取得する
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// 角度を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }
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
	// プレイヤーの向きを取得する
	DirectX::SimpleMath::Vector3 GetDirection() { return m_direction; }
	// 攻撃しているか取得する
	bool IsAttack();
	// バウンディングスフィアを取得する
	DirectX::BoundingSphere GetBoundingSphere() { return DirectX::BoundingSphere(m_position, COLLISION_SPHERE_SIZE); }
	// バウンディングボックスを取得する
	DirectX::BoundingBox GetBoundingBox() { return DirectX::BoundingBox(m_position, COLLISION_BOX_SIZE); }

public:
	// プレイヤーの待機状態を取得する
	PlayerIdling* GetPlayerIdling() { return m_playerIdling.get(); }
	// プレイヤーの走り状態を取得する
	PlayerRunning* GetPlayerRunning() { return m_playerRunning.get(); }
	// プレイヤーの回避状態を取得する
	PlayerRolling* GetPlayerRolling() { return m_playerRolling.get(); }
	// プレイヤーの通常攻撃状態を取得する
	PlayerAttackingNormal* GetPlayerAttackingNormal() { return m_playerAttackingNormal.get(); }
	// カメラを取得する
	NRLib::TPS_Camera* GetCamera() { return m_camera.get(); }

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

private:
	// 無敵処理
	void Invincible();
	// スタミナ回復処理
	void ChargeStamina();

private:
	// プレイヤーの初期位置
	const DirectX::SimpleMath::Vector3 PLAYER_INITIAL_POS = { 0.0f,1.0f,0.0f };
	// 重力加速度
	const float GRAVITY = 9.8f;
	// 最大体力
	static const int MAX_HP = 6;
	// 最大スタミナ
	static const int MAX_STAMINA = 6;
	// 無敵時間
	const float MAX_INVINCIBLE = 120.0f;
	// 当たり判定(球)のサイズ
	const float COLLISION_SPHERE_SIZE = 0.5f;
	// 当たり判定(箱)のサイズ
	const DirectX::SimpleMath::Vector3 COLLISION_BOX_SIZE = { 1.0f,1.0f,1.0f };

private:
	// 現在のステート
	IPlayerState* m_currentState;
	// 待機状態
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// 走り状態
	std::unique_ptr<PlayerRunning> m_playerRunning;
	// 回避状態
	std::unique_ptr<PlayerRolling> m_playerRolling;
	// 通常攻撃
	std::unique_ptr<PlayerAttackingNormal> m_playerAttackingNormal;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// UI
	std::unique_ptr<PlayerUIManager> m_playerUIManager; 
	// エフェクト
	std::unique_ptr<PlayerEffectManager> m_playerEffectManager; 
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 回転
	DirectX::SimpleMath::Quaternion m_angle;
	// 体力
	int m_hp;
	// スタミナ
	int m_stamina;
	// スタミナの回復カウント
	float m_chargeCnt;
	// 無敵
	bool m_invincible;
	// 無敵時間
	float m_invincibleTime;
	// プレイヤーの向き
	DirectX::SimpleMath::Vector3 m_direction;
};
