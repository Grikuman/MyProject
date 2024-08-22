/*
	@file	Player.h
	@brief	プレイヤーシーンクラス
*/
#pragma once
#include "IState.h"
#include "PlayerIdling.h"
#include "PlayerAttack.h"
#include "PlayerDash.h"

// 前方宣言
class CommonResources;
class GeometricPrimitive;
class Collision;



namespace NRLib
{
	class FixedCamera;
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
	void Initialize(CommonResources* resources);
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

	// ステートを変更する
	void ChangeState(IState* newState);
private:
	// 現在のステート
	IState* m_currentState;
	// 共通リソース
	CommonResources* m_commonResources;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// モデル
	std::unique_ptr<DirectX::Model> m_model;

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
};
