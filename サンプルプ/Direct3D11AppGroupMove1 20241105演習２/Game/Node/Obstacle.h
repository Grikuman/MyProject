#pragma once
#ifndef OBSTACLE_DEFINED
#define OBSTACLE_DEFINED
#include "Interface/IComposite.h"
#include "Node/NodeBase.h"

// 障害物を定義する
class Obstacle : public NodeBase//, IComponent
{
	// 部品ID
	enum PartID : int
	{
		OBSTACLE = -2,								// PartID: -2
	};

	// 障害物モデルスケール
	static const float OBSTACLE_MODEL_SCALE;

public:
	// ノード番号を取得する
	int GetNodeNumber() const { return m_nodeNumber; }
	// 部品IDを取得する
	int GetPartID() const { return 0; }
	// 部品番号を取得する
	int GetPartNumber() const { return 0; }
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
	DirectX::Model* GetModel() { return nullptr; }
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	// 衝突を取得する
	bool GetCollision() const { return m_collision; }
	// 衝突を設定する
	void SetCollision(bool collision) { m_collision = collision; }
public:
	// コンストラクタ
	Obstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	// デストラクタ
	~Obstacle();
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
	// 砲塔部品を追加する
	void Attach(std::unique_ptr<IComponent> turretPart);
	// 砲塔部品を削除する
	void Detach(std::unique_ptr<IComponent> turretPart);
	// 描画する
	inline void Render();
	// 後処理を行う
	void Finalize();

private:
	// グラフィックス
	Graphics* m_graphics;
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
	// 質量
	float m_mass;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 衝突
	bool m_collision;
};

#endif		// OBSTACLE_DEFINED
