#pragma once
#ifndef STEERING_BEHAVIOR_DEFINED
#define STEERING_BEHAVIOR_DEFINED

class Turret;
// ���Ǎs���N���X���`����
class SteeringBehavior
{
public:
	// ���Ǎs���^�C�v
	enum BEHAVIOR_TYPE { 	ARRIVE, SEPARATION, ALLIGNMENT, OBSTACLE_AVOIDANCE };

	// �s�����L�����ǂ����𒲂ׂ�
	bool On(BEHAVIOR_TYPE behaviorType) const { return (m_behaviorFlags & behaviorType) == behaviorType; }
	// �����s����L���ɂ���
	void ArriveOn() { m_behaviorFlags |= BEHAVIOR_TYPE::ARRIVE; }
	// �����s���𖳌��ɂ���
	void ArriveOff() { if (On(BEHAVIOR_TYPE::ARRIVE)) m_behaviorFlags ^= BEHAVIOR_TYPE::ARRIVE; }
	// �����s�����L�����ǂ����𒲂ׂ�
	bool IsArriveOn() const { return On(BEHAVIOR_TYPE::ARRIVE); }

	// �����s����L���ɂ���
	void SeparationOn() { m_behaviorFlags |= BEHAVIOR_TYPE::SEPARATION; }
	// �����s���𖳌��ɂ���
	void SeparationOff() { if (On(BEHAVIOR_TYPE::SEPARATION)) m_behaviorFlags ^= BEHAVIOR_TYPE::SEPARATION; }
	// �����s�����L�����ǂ����𒲂ׂ�
	bool IsSeparationOn() const { return On(BEHAVIOR_TYPE::SEPARATION); }

	// ����s����L���ɂ���
	void AllignmentOn() { m_behaviorFlags |= BEHAVIOR_TYPE::ALLIGNMENT; }
	// ����s���𖳌��ɂ���
	void AllignmentOff() { if (On(BEHAVIOR_TYPE::ALLIGNMENT)) m_behaviorFlags ^= BEHAVIOR_TYPE::ALLIGNMENT; }
	// ����s�����L�����ǂ����𒲂ׂ�
	bool IsAllignmentOn() const { return On(BEHAVIOR_TYPE::ALLIGNMENT); }

	// ��Q�������L���ɂ���
	void ObstacleAvoidanceOn() { m_behaviorFlags |= BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE; }
	// ��Q������𖳌��ɂ���
	void ObstacleAvoidanceOff() { if (On(BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE)) m_behaviorFlags ^= BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE; }
	// ��Q��������L�����ǂ����𒲂ׂ�
	bool IsObstacleAvoidanceOn() const { return On(BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE); }

	// �^�[�Q�b�g�̈ʒu��ݒ肷��
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) { m_targetPosition = targetPosition; }


public:
	// �R���X�g���N�^
	SteeringBehavior(Turret* turret);
	// ���Ǘ͂��v�Z����
	DirectX::SimpleMath::Vector3 Calculate();
	// ���Ǘ͂����Z����
	bool AccumulateForce(DirectX::SimpleMath::Vector3* force, const DirectX::SimpleMath::Vector3& applyForce);
	// �����s�����s��
	DirectX::SimpleMath::Vector3 Arrive(const DirectX::SimpleMath::Vector3& targetPosition);
	// �����s�����s��(�O���[�v�s��)
	DirectX::SimpleMath::Vector3 Separation();
	// ����s�����s��(�O���[�v�s��)
	DirectX::SimpleMath::Vector3 Alignment();
	// ��Q��������s��
	DirectX::SimpleMath::Vector3 ObstacleAvoidance(const DirectX::SimpleMath::Vector3& targetPosition);

private:
	// �C��
	Turret* m_turret;
	// �s���t���O
	int m_behaviorFlags;
	// �^�[�Q�b�g�ʒu
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// ���Ǘ�
	DirectX::SimpleMath::Vector3 m_steeringForce;
	// �}�[�J�[
	DirectX::SimpleMath::Vector3 m_marker;
	// �אږC���z��
	std::vector<Turret*> m_neighbors;
};

#endif		// STEERING_BEHAVIOR_DEFINED
