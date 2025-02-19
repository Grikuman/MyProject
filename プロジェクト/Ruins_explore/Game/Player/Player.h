/*
	ファイル名：Player.h
	　　　概要：プレイヤーの情報を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "PlayerWalk.h"
#include "PlayerAttack.h"
#include "PlayerDash.h"
#include "PlayerJump.h"

#include "Game/Interface/IPlayerPart.h"
#include "Parts/PlayerBody.h"
#include "Parts/PlayerRightHand.h"
#include "Parts/PlayerLeftHand.h"

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
	void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
	// 速度に係数をかける
	void ApplyVelocity(float scale) { m_velocity *= scale; }
	// 回転を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle = angle; }
	// 回転を加算する
	void AddAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle *= angle; }
	// 体力を設定する
	void SetHP(const int hp) { m_hp = hp; }
	// スタミナを設定する
	void SetStamina(const int stamina) { m_stamina = stamina; }
	//無敵を設定する
	void SetInvincible(const bool invincible) { m_invincible = invincible; }
	// ステートを変更する
	void ChangeState(IPlayerState* newState);

public:
	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 速度を取得する
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// 角度を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }
	// 体力を取得する
	int GetHP() const                                { return m_hp; }
	// 最大体力を取得する
	int GetMAXHP() const                             { return MAX_HP; }
	// スタミナを取得する
	int GetStamina() const                           { return m_stamina; }
	// 最大スタミナを取得する
	int GetMAXSTAMINA() const                        { return MAX_STAMINA; }
	// 無敵を取得
	bool GetInvincible() const                       { return m_invincible; }
	// プレイヤーの向きを取得する
	DirectX::SimpleMath::Vector3 GetForwardDirection();
	// 攻撃しているか取得する
	bool IsAttack();
	// バウンディングスフィアを取得する
	DirectX::BoundingSphere GetBoundingSphere();
	// バウンディングボックスを取得する
	DirectX::BoundingBox GetBoundingBox();
	// カメラを取得する
	NRLib::TPS_Camera* GetCamera()                   { return m_camera.get(); }

public:
	// プレイヤーアイドリングを取得する
	PlayerWalk* GetPlayerWalk() { return m_playerWalk.get(); }
	// プレイヤーアタックを取得する
	PlayerAttack* GetPlayerAttack() { return m_playerAttack.get(); }
	// プレイヤーダッシュを取得する
	PlayerDash* GetPlayerDash() { return m_playerDash.get(); }
	// プレイヤージャンプを取得する
	PlayerJump* GetPlayerJump() { return m_playerJump.get(); }


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
	// 重力加速度
	const float GRAVITY = 9.8f;
	// 最大体力
	static const int MAX_HP = 6;
	// 最大スタミナ
	static const int MAX_STAMINA = 6;

private:
	// UI管理クラス
	std::unique_ptr<PlayerUIManager> m_playerUIManager;
	// エフェクト管理クラス
	std::unique_ptr<PlayerEffectManager> m_playerEffectManager;
	// 現在のステート
	IPlayerState* m_currentState;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;

	// プレイヤーのパーツ
	std::vector<std::unique_ptr<IPlayerPart>> m_parts;

	// アイドリング状態
	std::unique_ptr<PlayerWalk>   m_playerWalk;
	// アタック状態
	std::unique_ptr<PlayerAttack> m_playerAttack;
	// ダッシュ状態
	std::unique_ptr<PlayerDash>   m_playerDash;
	// ジャンプ状態
	std::unique_ptr<PlayerJump> m_playerJump;

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
};
