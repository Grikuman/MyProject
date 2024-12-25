#include "Framework/pch.h"
#include "Steering/SteeringBehavior.h"
#include "Steering/SteeringBehaviorParameter.h"
#include "Framework/Common.h"
#include "Observer/Messenger.h"
#include "Turret/Header/Turret.h"
#include "Node/NodeFactory.h"
#include <algorithm>

// コンストラクタ
SteeringBehavior::SteeringBehavior(Turret* turret)
	:
	m_turret(turret),																							// 砲塔
	m_behaviorFlags(0),																					// 行動フラグ
	m_targetPosition(DirectX::SimpleMath::Vector3::Zero),		// ターゲット位置
	m_steeringForce(DirectX::SimpleMath::Vector3::Zero),		// 操舵力
	m_marker{},																									// マーカー
	m_neighbors{}																								// 隣接者
{
}

// 操舵力を計算する
DirectX::SimpleMath::Vector3 SteeringBehavior::Calculate()
{
	using namespace DirectX::SimpleMath;
	// 適用される力
	Vector3 force(Vector3::Zero);
	// 操舵力をリセットする
	m_steeringForce = Vector3::Zero;

	// 整列行動
	if (On(BEHAVIOR_TYPE::ALLIGNMENT) && GetRandomFloat() < SteeringBehaviorParameter::ALIGNMENT_PROBABILITY)
	{
		// 整列行動の操舵力を加算する
		force += Alignment() * SteeringBehaviorParameter::ALIGNMENT_WEIGHT / SteeringBehaviorParameter::ALIGNMENT_PROBABILITY;
		// 操舵力が自分自身に適用する最大の力を超えないようにする
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// 到着行動
	if (On(BEHAVIOR_TYPE::ARRIVE))
	{
		// 到着行動を行う
		force += Arrive(m_targetPosition) * SteeringBehaviorParameter::ARRIVE_WEIGHT;
		// 操舵力が最大の力を超えないようにする
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// 分離行動
	if (On(BEHAVIOR_TYPE::SEPARATION))
	{
		// 隣接者配列を取得する
		m_neighbors = m_turret->GetNeighbors();
		// 分離行動の操舵力を加算する
		force += Separation() * SteeringBehaviorParameter::SEPARATION_WEIGHT;
		// 操舵力が最大の力を超えないようにする
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// 障害物回避行動
	if (On(BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE))
	{
		// 障害物回避行動を行う
		force += ObstacleAvoidance(m_targetPosition) * SteeringBehaviorParameter::OBSTACLE_AVOIDANCE_WEIGHT;
		// 操舵力が最大の力を超えないようにする
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// 操舵力を返す
	return m_steeringForce;
}

// 操舵力を加算する
bool SteeringBehavior::AccumulateForce(DirectX::SimpleMath::Vector3* force, const DirectX::SimpleMath::Vector3& applyForce)
{
	using namespace DirectX::SimpleMath;

	// これまでに加算された力
	float appliedForce = (*force).Length();
	// 残りの加算可能な力	
	float remainingForce = m_turret->GetMaxForce() - appliedForce;
	// さらに力を加算可能かどうかを調べる
	if (remainingForce <= 0.0f) { 	return false; }
	// 加算される力の大きさを設定する
	float magnitudeToApply = applyForce.Length();
	// 全ての力を加算可能かどうかを調べる
	if (magnitudeToApply < remainingForce)
	{ 
		// 全ての力を加算する
		*force += applyForce;
	}
	else
	{
		Vector3 applyForceL = applyForce;
		// 加算された力を正規化する
		applyForceL.Normalize();
		// 限界まで力を加算する
		*force += applyForceL * remainingForce;
	}
	// 力を加算ができる
	return true;
}

// 到着行動を行う
DirectX::SimpleMath::Vector3 SteeringBehavior::Arrive(const DirectX::SimpleMath::Vector3& targetPosition)
{
	using namespace DirectX::SimpleMath;

	// ターゲットへのベクトルを設定する
	Vector3 toTarget = targetPosition - m_turret->GetPosition();
	// ターゲット間の距離を計算する
	float distance = toTarget.Length();
	// ターゲットへの距離が0.01より大きい場合
	if (distance > 0.01f)
	{
		// 減速調整パラメータ
		const float DECELERRATION_TWEAKER = 0.25f;
		// ターゲットまでの距離に比例して移動速度を設定する
		float speed = distance / 1.0f * DECELERRATION_TWEAKER;
		// 最大移動速度を超えないようにする
		speed = std::min(speed, m_turret->GetMaxSpeed());
		// 速度を計算する
		Vector3 desiredVelocity = toTarget * speed / distance;
		// 操舵力を返す
		return desiredVelocity - m_turret->GetVelocity();
	}
	// それ以外の操舵力を返す
	return Vector3::Zero;
}

// 分離行動(グループ行動)
// エージェントを近接領域にいるものから離す操舵力を作る
DirectX::SimpleMath::Vector3 SteeringBehavior::Separation()
{
	using namespace DirectX::SimpleMath;

	// 操舵力
	Vector3 steeringForce(Vector3::Zero);
	for (int index = 0; index < m_neighbors.size(); index++)
	{
			// 自砲塔と他砲塔までのベクトルを取得する
			Vector3 toTurret = m_turret->GetPosition() - m_neighbors[index]->GetPosition();
			// 正規化する
			toTurret.Normalize();
			// 自砲塔と他砲塔間の距離に反比例して力をスケーリングする
			steeringForce += toTurret / toTurret.Length();
	}
	// 操舵力を返す
	return steeringForce;
}

// 整列行動を行う
// 個体の向きを整列する操舵力を返す
DirectX::SimpleMath::Vector3 SteeringBehavior::Alignment()
{
	using namespace DirectX::SimpleMath;

	// 砲塔の方向総和ベクトル
	Vector3 headingSum = Vector3::Zero;
	// 砲塔の方向平均ベクトル
	Vector3 HeadingAverage = Vector3::Zero;
	// 近接個体数をカウントする
	int neighborCount = 0;
	// 方向ベクトルの総和を計算する  
	for (int index = 0; index < m_neighbors.size(); index++)
	{
		// 方向ベクトルの総和を計算する
		headingSum += m_neighbors[index]->GetHeading();
		// 個体のカウントする
		neighborCount++;
	}
	// 方向ベクトルを平均化する
	if (neighborCount > 0)
	{
		// 方向総和ベクトルの平均を計算する
		HeadingAverage = headingSum / (float)neighborCount;
		// 方向平均ベクトルから自砲塔の向きを減らす
		HeadingAverage -= m_turret->GetHeading();
	}
	// 方向ベクトルの平均値を返す
	return HeadingAverage;
}

// 障害物を回避する
DirectX::SimpleMath::Vector3 SteeringBehavior::ObstacleAvoidance(const DirectX::SimpleMath::Vector3& targetPosition)
{
	using namespace DirectX::SimpleMath;

	// 障害物への距離
	const float OBSTACLE_DISTANCE = 100.0f;
	// 障害物の半径
	const float OBSTACLE_RADIUS = 30.0f;
	// 最大回避力
	const float MAX_AVOIDANCE_FORCE = 20.0f;

	// 回避力を宣言する
	Vector3 avoidanceForce = Vector3::Zero;
	// 危険度スコアの最大値を宣言する
	float highestDangerScore = 0.0f;
	// 最も危険な障害物を宣言する
	IComponent* mostDangerousObstacle = nullptr;  
	// ターゲットへのベクトルを計算する
	Vector3 toTarget = targetPosition - m_turret->GetPosition();
	// すべての障害物の中から最も危険な障害物(距離が短く、進行方向に近い障害物)を検出する
	for (const auto& obstacle : NodeFactory::GetObstacles())
	{
		// 障害物へのポインタを計算する
		Vector3 toObstacle = obstacle->GetPosition() - m_turret->GetPosition();
		// 障害物への距離を計算する
		float toObstacleDistance = toObstacle.Length();

		// 障害物が回避距離内にあり、進行方向に存在する場合
		if (toObstacleDistance < (OBSTACLE_DISTANCE + OBSTACLE_RADIUS) && toTarget.Dot(toObstacle) > 0)
		{
			// 砲塔の進行方向ベクトルを計算する
			Vector3 turretHeading = m_turret->GetVelocity();
			// 正規化する
			turretHeading.Normalize();
			// 実際の距離を計算する
			float actualDistance = toObstacleDistance - OBSTACLE_RADIUS;
			// 距離の逆数を用いて危険度スコアを計算する
			float distanceScore = 1.0f / std::max(actualDistance, 1.0f);
			// 砲塔の進行方向と障害物の方向の角度に基づく危険度スコアを計算する
			float angleScore = turretHeading.Dot(toObstacle) / toObstacle.Length();
			// 総合的な危険度スコアを計算
			float dangerScore = distanceScore * angleScore;

			// 危険度がこれまでで最大なら、最も危険な障害物として記録する
			if (dangerScore > highestDangerScore) 
			{
				// 最も危険なスコアを設定する
				highestDangerScore = dangerScore;
				// 最も危険な障害物を設定する
				mostDangerousObstacle = obstacle;
			}
		}
	}

	// 最も危険な障害物に対して回避力を適用する
	if (mostDangerousObstacle)
	{
		// 障害物へのベクトルを計算する
		Vector3 toObstacle = mostDangerousObstacle->GetPosition() - m_turret->GetPosition();
		// 砲塔の向きを設定する
		Vector3 turretHeading = m_turret->GetVelocity();
		// 正規化する
		turretHeading.Normalize();
		// 砲塔の向きと障害物との外積を計算する
		Vector3 crossProduct = turretHeading.Cross(toObstacle);
		// 左右を判定する
		float sideSign = crossProduct.y > 0.0f ? 1.0f : -1.0f;
		// 横方向の回避を計算する
		Vector3 sideAvoidance = turretHeading.Cross(Vector3::UnitY) * sideSign;
		// 距離に基づいて回避力を計算し、危険度スコアを反映する
		float distanceFactor = pow((OBSTACLE_DISTANCE + OBSTACLE_RADIUS) / toObstacle.Length(), 2.0f);
		// 回避力を計算する
		avoidanceForce = sideAvoidance * distanceFactor * highestDangerScore;
	}

	// 回避力の上限を適用する
	if (avoidanceForce.Length() > MAX_AVOIDANCE_FORCE) 
	{
		// 回避力を正規化する
		avoidanceForce.Normalize();
		// 回避力を最大化する
		avoidanceForce *= MAX_AVOIDANCE_FORCE;
	}
	// 回避力を返す
	return avoidanceForce;
}

