#pragma once
#ifndef STEERING_BEHAVIOR_PARAMETER_DEFINED
#define STEERING_BEHAVIOR_PARAMETER_DEFINED

// 行動パラメータ
class SteeringBehaviorParameter
{
public:
	// 最大移動速度(1秒あたりのドット数)
	static const float MAX_SPEED;
	// 適用される最大力
	static const float MAX_FORCE;
	// 最大回転率（ラジアン/秒）
	static const float MAX_TURN_RATE;
	// 操舵力に掛ける調整用のパラメータ
	static const float STEERING_FORCE_TWEAKER;
	// 到着行動の調整用のウエイト
	static const float ARRIVE_WEIGHT;
	// 分離行動の調整用のウエイト
	static const float SEPARATION_WEIGHT;
	// 整列行動の調整用のウエイト
	static const float ALIGNMENT_WEIGHT;
	// 障害物回避行動の調整用のウエイト
	static const float OBSTACLE_AVOIDANCE_WEIGHT;

	// 分離確率
	static const float SEPARATION_PROBABILITY;
	// 整列確率
	static const float ALIGNMENT_PROBABILITY;
};

#endif		// STEERING_BEHAVIOR_PARAMETER_DEFINED
