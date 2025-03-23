#include "Framework/pch.h"
#include "Steering/SteeringBehaviorParameter.h"

// 最大移動速度(1秒あたりのドット数)
const float SteeringBehaviorParameter::MAX_SPEED = 1000.0f;
// 適用される最大力
const float SteeringBehaviorParameter::MAX_FORCE = STEERING_FORCE_TWEAKER * 40.0f;
// 最大回転率（ラジアン/秒）
const float SteeringBehaviorParameter::MAX_TURN_RATE = DirectX::XM_PI / 2.0f;
// 操舵力に掛ける調整用のパラメータ
const float SteeringBehaviorParameter::STEERING_FORCE_TWEAKER = 500.0f;

// 到着行動の調整用ウエイト
const float SteeringBehaviorParameter::ARRIVE_WEIGHT = STEERING_FORCE_TWEAKER * 4.0f;
// 分離行動の調整用ウエイト
const float SteeringBehaviorParameter::SEPARATION_WEIGHT = STEERING_FORCE_TWEAKER * 40.0f;
// 整列行動の調整用ウエイト
const float SteeringBehaviorParameter::ALIGNMENT_WEIGHT = STEERING_FORCE_TWEAKER * 4.0f;	
// 障害物回避行動の調整用ウエイト
const float SteeringBehaviorParameter::OBSTACLE_AVOIDANCE_WEIGHT = STEERING_FORCE_TWEAKER * 40.0f;

// 分離確率
const float SteeringBehaviorParameter::SEPARATION_PROBABILITY = 0.8f;
// 整列確率
const float SteeringBehaviorParameter::ALIGNMENT_PROBABILITY = 1.0f;
