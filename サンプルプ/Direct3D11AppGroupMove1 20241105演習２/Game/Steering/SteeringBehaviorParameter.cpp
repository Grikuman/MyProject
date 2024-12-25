#include "Framework/pch.h"
#include "Steering/SteeringBehaviorParameter.h"

// �ő�ړ����x(1�b������̃h�b�g��)
const float SteeringBehaviorParameter::MAX_SPEED = 1000.0f;
// �K�p�����ő��
const float SteeringBehaviorParameter::MAX_FORCE = STEERING_FORCE_TWEAKER * 40.0f;
// �ő��]���i���W�A��/�b�j
const float SteeringBehaviorParameter::MAX_TURN_RATE = DirectX::XM_PI / 2.0f;
// ���Ǘ͂Ɋ|���钲���p�̃p�����[�^
const float SteeringBehaviorParameter::STEERING_FORCE_TWEAKER = 500.0f;

// �����s���̒����p�E�G�C�g
const float SteeringBehaviorParameter::ARRIVE_WEIGHT = STEERING_FORCE_TWEAKER * 4.0f;
// �����s���̒����p�E�G�C�g
const float SteeringBehaviorParameter::SEPARATION_WEIGHT = STEERING_FORCE_TWEAKER * 40.0f;
// ����s���̒����p�E�G�C�g
const float SteeringBehaviorParameter::ALIGNMENT_WEIGHT = STEERING_FORCE_TWEAKER * 4.0f;	
// ��Q������s���̒����p�E�G�C�g
const float SteeringBehaviorParameter::OBSTACLE_AVOIDANCE_WEIGHT = STEERING_FORCE_TWEAKER * 40.0f;

// �����m��
const float SteeringBehaviorParameter::SEPARATION_PROBABILITY = 0.8f;
// ����m��
const float SteeringBehaviorParameter::ALIGNMENT_PROBABILITY = 1.0f;
