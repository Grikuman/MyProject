#pragma once
#ifndef TURRET_DEFINED
#define TURRET_DEFINED
#include "Interface/IComposite.h"
#include "Interface/ICollision.h"
#include "Interface/IBullet.h"
#include "Steering/SteeringBehavior.h"

// 「砲塔」クラスを定義する
class Turret : public IComposite
{
public:
	// 部品ID
	enum PartID : int
	{
		TURRET = -1,								// PartID:-1
		TURRET_BOTTOM = 0,			// PartID:0
		TURRET_FOOT,							// PartID:1
		TURRET_MIDDLE,					// PartID:2
		TURRET_PLATE,						// PartID:3
		TURRET_TOP,								// PartID:4
		TURRET_FORT,							// PartID:5
		TURRET_GUN								// PartID:6
	};

public:
	// 最大砲弾数
	static const int MAX_BULLET_NUMBER;
	// スピート
	static const DirectX::SimpleMath::Vector3 SPEED;
	// 水平回転角
	static const float HORIZONTAL_ROTATION_ANGLE;
	// 垂直回転角
	static const float VERTICAL_ROTATION_ANGLE;
	// 砲塔モデルスケール
	static const DirectX::SimpleMath::Vector3 TURRET_MODEL_SCALE;
	// 砲塔境界ボックススケール
	static const DirectX::SimpleMath::Vector3 TURRET_BOUNDINGBOX_SCALE;

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
	DirectX::SimpleMath::Vector3 GetPosition() const {	return m_currentPosition; }
	// 現在の位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// 速度を取得する
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// 方向を取得する
	DirectX::SimpleMath::Vector3 GetHeading() const { return m_heading; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// 質量を取得する
	float GetMass() const { return m_mass; }
	// 質量を設定する
	void SetMass(const float& mass) { m_mass = mass; }
	// モデルを取得する
	DirectX::Model* GetModel() { return nullptr; }
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	// 「砲弾」を参照する
	std::vector<std::unique_ptr<IBullet>>& GetBullets() { return m_bullets; };
	// 衝突を取得する
	bool GetCollision() const { return m_collision; }
	// 衝突を設定する
	void SetCollision(bool collision) { m_collision = collision; }
	// 隣接砲塔配列を取得する
	 std::vector<Turret*> GetNeighbors() { return m_neighbors; }
	// 最大移動速度を取得する
	float GetMaxSpeed() const { return m_maxSpeed; }
	// 最大の力を取得する
	float GetMaxForce() const { return m_maxForce; }

	// 到着行動を行う(ターゲットの位置を設定し到着行動を有効にする)
	void ArriveOn(const DirectX::SimpleMath::Vector3& position) { m_steeringBehavior->SetTargetPosition(position); m_steeringBehavior->ArriveOn(); }
	// 整列行動を行う(整列行動を有効にする)
	void AlignmentOn() { m_steeringBehavior->AllignmentOn(); }
	// 分離行動を行う(分離行動を有効にする)
	void SeparationOn() { m_steeringBehavior->SeparationOn(); }
	// 障害物分離行動を行う(障害物分離行動を有効にする)
	void ObstacleAvoidanceOn(const DirectX::SimpleMath::Vector3& position) { m_steeringBehavior->SetTargetPosition(position); m_steeringBehavior->ObstacleAvoidanceOn(); }
	// 移動しているかどうかを取得する
	bool IsMove() const { return m_move; }
	// 移動開始/停止する
	void Move(bool start) { m_move = start; }

public:
	// コンストラクタ
	Turret(IComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	// デストラクタ
	~Turret();
	// 初期化する
	void Initialize();
	// 通知する(キーボード)
	inline void OnKeyPressed(const DirectX::Keyboard::Keys& keys);
	// 通知する(マウス)
	void OnLeftButtonClicked(const DirectX::SimpleMath::Vector3& position);
	// 更新する
	inline void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle);
	// 砲塔境界球を作成する
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);
	// 衝突判定を準備する
	void PrepareCollision(ICollisionVisitor* visitor);
	// 衝突判定する
	inline void DetectCollision(ICollisionVisitor* visitor, IBullet* bullet);
	// 砲塔と砲弾の衝突判定を行う
	inline void DetectCollisionTurret();
	// 砲塔部品を追加する
	void Attach(std::unique_ptr<IComponent> turretPart);
	// 砲塔部品を削除する
	void Detach(std::unique_ptr<IComponent> turretPart);
	// 描画する
	inline void Render();
	// 砲塔境界球を描画する
	inline void DrawTurretBoundingSphere(bool collision);
	// 後処理を行う
	void Finalize();
	// 砲弾をチャージする
	void ChargeBullets();
	// 近接砲塔を生成する(プレイシーンから呼び出される)
	void CreateNeighbors(std::vector<int>& teamList);

public:
	// 砲塔部品番号をリセットする(-1から開始する)
	static int ResetPartsNumber() { s_partsNumber = -1;  return s_partsNumber; }
	// 砲塔部品番号を取得する
	static int GetPartsNumber() { return s_partsNumber; }
	// 砲塔部品番号増やす
	static void IncrementPartsNumber() { s_partsNumber++; }
	// 砲塔部品番号のインクリメント後に砲塔部品番号を取得する
	static int GetPartsNumberAfterIncrement() { return ++s_partsNumber; }

private:
	// 砲塔部品カウント
	static int s_partsNumber;

private:
	// グラフィックス
	Graphics* m_graphics;
	// 衝突ビジター
	ICollisionVisitor* m_collisionVisitor;
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
	// 砲塔回転角
	DirectX::SimpleMath::Quaternion m_rotationTurretAngle;
	// 砲塔速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 加速度
	DirectX::SimpleMath::Vector3 m_acceleration;
	// 進行方向ベクトル
	DirectX::SimpleMath::Vector3 m_heading;
	// 最大移動速度
	float m_maxSpeed;
	// 最大回転比率(ラジアン/秒)
	float m_maxTurnRate;
	// 適用される最大力
	float m_maxForce;
	// 質量
	float m_mass;
	// 砲塔部品配列
	std::vector<std::unique_ptr<IComponent>> m_turretParts;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 砲弾配列
	std::vector<std::unique_ptr<IBullet>> m_bullets;
	// 砲塔境界球
	DirectX::BoundingSphere m_turretBoundingSphere;
	// 砲塔中心点
	DirectX::SimpleMath::Vector3 m_turretCenter;
	// 衝突
	bool m_collision;
	// 移動フラグ
	bool m_move;
	// 隣接砲塔配列
	 std::vector<Turret*> m_neighbors;
	 // 操舵行動
	std::unique_ptr<SteeringBehavior> m_steeringBehavior;

};

#endif		// TURRET_DEFINED
