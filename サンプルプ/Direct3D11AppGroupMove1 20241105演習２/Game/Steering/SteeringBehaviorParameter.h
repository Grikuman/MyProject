#pragma once
#ifndef STEERING_BEHAVIOR_PARAMETER_DEFINED
#define STEERING_BEHAVIOR_PARAMETER_DEFINED

// �s���p�����[�^
class SteeringBehaviorParameter
{
public:
	// �ő�ړ����x(1�b������̃h�b�g��)
	static const float MAX_SPEED;
	// �K�p�����ő��
	static const float MAX_FORCE;
	// �ő��]���i���W�A��/�b�j
	static const float MAX_TURN_RATE;
	// ���Ǘ͂Ɋ|���钲���p�̃p�����[�^
	static const float STEERING_FORCE_TWEAKER;
	// �����s���̒����p�̃E�G�C�g
	static const float ARRIVE_WEIGHT;
	// �����s���̒����p�̃E�G�C�g
	static const float SEPARATION_WEIGHT;
	// ����s���̒����p�̃E�G�C�g
	static const float ALIGNMENT_WEIGHT;
	// ��Q������s���̒����p�̃E�G�C�g
	static const float OBSTACLE_AVOIDANCE_WEIGHT;

	// �����m��
	static const float SEPARATION_PROBABILITY;
	// ����m��
	static const float ALIGNMENT_PROBABILITY;
};

#endif		// STEERING_BEHAVIOR_PARAMETER_DEFINED
