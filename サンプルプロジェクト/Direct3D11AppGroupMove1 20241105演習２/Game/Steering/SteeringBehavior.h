#pragma once
#ifndef STEERING_BEHAVIOR_DEFINED
#define STEERING_BEHAVIOR_DEFINED

class Turret;
// 操舵行動クラスを定義する
class SteeringBehavior
{
public:
	// 操舵行動タイプ
	enum BEHAVIOR_TYPE { 	ARRIVE, SEPARATION, ALLIGNMENT, OBSTACLE_AVOIDANCE };

	// 行動が有効かどうかを調べる
	bool On(BEHAVIOR_TYPE behaviorType) const { return (m_behaviorFlags & behaviorType) == behaviorType; }
	// 到着行動を有効にする
	void ArriveOn() { m_behaviorFlags |= BEHAVIOR_TYPE::ARRIVE; }
	// 到着行動を無効にする
	void ArriveOff() { if (On(BEHAVIOR_TYPE::ARRIVE)) m_behaviorFlags ^= BEHAVIOR_TYPE::ARRIVE; }
	// 到着行動が有効かどうかを調べる
	bool IsArriveOn() const { return On(BEHAVIOR_TYPE::ARRIVE); }

	// 分離行動を有効にする
	void SeparationOn() { m_behaviorFlags |= BEHAVIOR_TYPE::SEPARATION; }
	// 分離行動を無効にする
	void SeparationOff() { if (On(BEHAVIOR_TYPE::SEPARATION)) m_behaviorFlags ^= BEHAVIOR_TYPE::SEPARATION; }
	// 分離行動が有効かどうかを調べる
	bool IsSeparationOn() const { return On(BEHAVIOR_TYPE::SEPARATION); }

	// 整列行動を有効にする
	void AllignmentOn() { m_behaviorFlags |= BEHAVIOR_TYPE::ALLIGNMENT; }
	// 整列行動を無効にする
	void AllignmentOff() { if (On(BEHAVIOR_TYPE::ALLIGNMENT)) m_behaviorFlags ^= BEHAVIOR_TYPE::ALLIGNMENT; }
	// 整列行動が有効かどうかを調べる
	bool IsAllignmentOn() const { return On(BEHAVIOR_TYPE::ALLIGNMENT); }

	// 障害物回避を有効にする
	void ObstacleAvoidanceOn() { m_behaviorFlags |= BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE; }
	// 障害物回避を無効にする
	void ObstacleAvoidanceOff() { if (On(BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE)) m_behaviorFlags ^= BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE; }
	// 障害物回避が有効かどうかを調べる
	bool IsObstacleAvoidanceOn() const { return On(BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE); }

	// ターゲットの位置を設定する
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) { m_targetPosition = targetPosition; }


public:
	// コンストラクタ
	SteeringBehavior(Turret* turret);
	// 操舵力を計算する
	DirectX::SimpleMath::Vector3 Calculate();
	// 操舵力を加算する
	bool AccumulateForce(DirectX::SimpleMath::Vector3* force, const DirectX::SimpleMath::Vector3& applyForce);
	// 到着行動を行う
	DirectX::SimpleMath::Vector3 Arrive(const DirectX::SimpleMath::Vector3& targetPosition);
	// 分離行動を行う(グループ行動)
	DirectX::SimpleMath::Vector3 Separation();
	// 整列行動を行う(グループ行動)
	DirectX::SimpleMath::Vector3 Alignment();
	// 障害物回避を行う
	DirectX::SimpleMath::Vector3 ObstacleAvoidance(const DirectX::SimpleMath::Vector3& targetPosition);

private:
	// 砲塔
	Turret* m_turret;
	// 行動フラグ
	int m_behaviorFlags;
	// ターゲット位置
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// 操舵力
	DirectX::SimpleMath::Vector3 m_steeringForce;
	// マーカー
	DirectX::SimpleMath::Vector3 m_marker;
	// 隣接砲塔配列
	std::vector<Turret*> m_neighbors;
};

#endif		// STEERING_BEHAVIOR_DEFINED
