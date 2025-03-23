#pragma once
#ifndef TURRET_GUN_DEFINED
#define TURRET_GUN_DEFINED
#include "Interface/ILeaf.h"
#include "Turret.h"

// 砲身クラス
class TurretGun : public ILeaf
{
	// インターバル
	const float SHOT_INTERVAL = 0.4f;
	// コマンドインターバル
	const float COMMAND_SHOT_INTERVAL = 1.8f;
public:
	// ノード番号を取得する
	int GetNodeNumber() const { return m_nodeNumber; }
	// 部品IDを取得する
	int GetPartID() const { return m_partID; }
	// 部品番号を取得する
	int GetPartNumber() const { return m_partNumber; }
	// 親を取得する
	IComponent* GetParent() const { return m_parent; }
	// 現在の位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	// 現在の位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// 質量を取得する
	float GetMass() const { return m_mass; }
	// 質量を設定する
	void SetMass(const float& mass) { m_mass = mass; }
	// モデルを取得する
	DirectX::Model* GetModel() { return m_model; }
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	// 砲弾を発射する
	void Shoot(IBullet* bullet);
	// 衝突を取得する
	bool GetCollision() const { return m_collision; }
	// 衝突を設定する
	void SetCollision(bool collision) { m_collision = collision; }

public:
	// コンストラクタ
	TurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	// デストラクタ
	~TurretGun();
	// 初期化する
	void Initialize();
	// 通知する
	inline void OnKeyPressed(const DirectX::Keyboard::Keys& keys);
	// 更新する
	inline void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle);
	// 衝突判定を準備する
	void PrepareCollision(ICollisionVisitor* visitor);
	// 衝突判定する
	void DetectCollision(ICollisionVisitor* visitor, IBullet* bullet);
	// 描画する
	inline void Render();
	// 後処理を行う
	void Finalize();

private:
	// グラフィックス
	Graphics* m_graphics;
	// 衝突ビジター
	ICollisionVisitor* m_collisionVisitor;
	// モデル
	DirectX::Model* m_model;
	// 親
	IComponent* m_parent;
	// ノード番号
	int m_nodeNumber;
	// 部品番号
	int m_partNumber;
	// 部品ID
	int m_partID;
	// 初期位置
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// 砲身回転角
	DirectX::SimpleMath::Quaternion m_rotationGunAngle;
	// 砲弾回転角
	DirectX::SimpleMath::Quaternion m_bulletAngle;
	// 質量
	float m_mass;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 砲塔
	Turret* m_turret;
	// 使用済み砲弾数
	int m_shotBulletNumber;
	// 砲弾発射タイマー
	float m_shotTimer;
	// タイマー
	DX::StepTimer m_timer;
	// 衝突
	bool m_collision;
};

#endif		// TURRET_GUN_DEFINED
