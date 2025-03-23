#include "Framework/pch.h"
#include "Steering/SteeringBehavior.h"
#include "Steering/SteeringBehaviorParameter.h"
#include "Framework/Common.h"
#include "Observer/Messenger.h"
#include "Turret/Header/Turret.h"
#include "Node/NodeFactory.h"
#include <algorithm>

// �R���X�g���N�^
SteeringBehavior::SteeringBehavior(Turret* turret)
	:
	m_turret(turret),																							// �C��
	m_behaviorFlags(0),																					// �s���t���O
	m_targetPosition(DirectX::SimpleMath::Vector3::Zero),		// �^�[�Q�b�g�ʒu
	m_steeringForce(DirectX::SimpleMath::Vector3::Zero),		// ���Ǘ�
	m_marker{},																									// �}�[�J�[
	m_neighbors{}																								// �אڎ�
{
}

// ���Ǘ͂��v�Z����
DirectX::SimpleMath::Vector3 SteeringBehavior::Calculate()
{
	using namespace DirectX::SimpleMath;
	// �K�p������
	Vector3 force(Vector3::Zero);
	// ���Ǘ͂����Z�b�g����
	m_steeringForce = Vector3::Zero;

	// ����s��
	if (On(BEHAVIOR_TYPE::ALLIGNMENT) && GetRandomFloat() < SteeringBehaviorParameter::ALIGNMENT_PROBABILITY)
	{
		// ����s���̑��Ǘ͂����Z����
		force += Alignment() * SteeringBehaviorParameter::ALIGNMENT_WEIGHT / SteeringBehaviorParameter::ALIGNMENT_PROBABILITY;
		// ���Ǘ͂��������g�ɓK�p����ő�̗͂𒴂��Ȃ��悤�ɂ���
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// �����s��
	if (On(BEHAVIOR_TYPE::ARRIVE))
	{
		// �����s�����s��
		force += Arrive(m_targetPosition) * SteeringBehaviorParameter::ARRIVE_WEIGHT;
		// ���Ǘ͂��ő�̗͂𒴂��Ȃ��悤�ɂ���
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// �����s��
	if (On(BEHAVIOR_TYPE::SEPARATION))
	{
		// �אڎҔz����擾����
		m_neighbors = m_turret->GetNeighbors();
		// �����s���̑��Ǘ͂����Z����
		force += Separation() * SteeringBehaviorParameter::SEPARATION_WEIGHT;
		// ���Ǘ͂��ő�̗͂𒴂��Ȃ��悤�ɂ���
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// ��Q������s��
	if (On(BEHAVIOR_TYPE::OBSTACLE_AVOIDANCE))
	{
		// ��Q������s�����s��
		force += ObstacleAvoidance(m_targetPosition) * SteeringBehaviorParameter::OBSTACLE_AVOIDANCE_WEIGHT;
		// ���Ǘ͂��ő�̗͂𒴂��Ȃ��悤�ɂ���
		if (!AccumulateForce(&m_steeringForce, force)) { return m_steeringForce; }
	}

	// ���Ǘ͂�Ԃ�
	return m_steeringForce;
}

// ���Ǘ͂����Z����
bool SteeringBehavior::AccumulateForce(DirectX::SimpleMath::Vector3* force, const DirectX::SimpleMath::Vector3& applyForce)
{
	using namespace DirectX::SimpleMath;

	// ����܂łɉ��Z���ꂽ��
	float appliedForce = (*force).Length();
	// �c��̉��Z�\�ȗ�	
	float remainingForce = m_turret->GetMaxForce() - appliedForce;
	// ����ɗ͂����Z�\���ǂ����𒲂ׂ�
	if (remainingForce <= 0.0f) { 	return false; }
	// ���Z�����͂̑傫����ݒ肷��
	float magnitudeToApply = applyForce.Length();
	// �S�Ă̗͂����Z�\���ǂ����𒲂ׂ�
	if (magnitudeToApply < remainingForce)
	{ 
		// �S�Ă̗͂����Z����
		*force += applyForce;
	}
	else
	{
		Vector3 applyForceL = applyForce;
		// ���Z���ꂽ�͂𐳋K������
		applyForceL.Normalize();
		// ���E�܂ŗ͂����Z����
		*force += applyForceL * remainingForce;
	}
	// �͂����Z���ł���
	return true;
}

// �����s�����s��
DirectX::SimpleMath::Vector3 SteeringBehavior::Arrive(const DirectX::SimpleMath::Vector3& targetPosition)
{
	using namespace DirectX::SimpleMath;

	// �^�[�Q�b�g�ւ̃x�N�g����ݒ肷��
	Vector3 toTarget = targetPosition - m_turret->GetPosition();
	// �^�[�Q�b�g�Ԃ̋������v�Z����
	float distance = toTarget.Length();
	// �^�[�Q�b�g�ւ̋�����0.01���傫���ꍇ
	if (distance > 0.01f)
	{
		// ���������p�����[�^
		const float DECELERRATION_TWEAKER = 0.25f;
		// �^�[�Q�b�g�܂ł̋����ɔ�Ⴕ�Ĉړ����x��ݒ肷��
		float speed = distance / 1.0f * DECELERRATION_TWEAKER;
		// �ő�ړ����x�𒴂��Ȃ��悤�ɂ���
		speed = std::min(speed, m_turret->GetMaxSpeed());
		// ���x���v�Z����
		Vector3 desiredVelocity = toTarget * speed / distance;
		// ���Ǘ͂�Ԃ�
		return desiredVelocity - m_turret->GetVelocity();
	}
	// ����ȊO�̑��Ǘ͂�Ԃ�
	return Vector3::Zero;
}

// �����s��(�O���[�v�s��)
// �G�[�W�F���g���ߐڗ̈�ɂ�����̂��痣�����Ǘ͂����
DirectX::SimpleMath::Vector3 SteeringBehavior::Separation()
{
	using namespace DirectX::SimpleMath;

	// ���Ǘ�
	Vector3 steeringForce(Vector3::Zero);
	for (int index = 0; index < m_neighbors.size(); index++)
	{
			// ���C���Ƒ��C���܂ł̃x�N�g�����擾����
			Vector3 toTurret = m_turret->GetPosition() - m_neighbors[index]->GetPosition();
			// ���K������
			toTurret.Normalize();
			// ���C���Ƒ��C���Ԃ̋����ɔ���Ⴕ�ė͂��X�P�[�����O����
			steeringForce += toTurret / toTurret.Length();
	}
	// ���Ǘ͂�Ԃ�
	return steeringForce;
}

// ����s�����s��
// �̂̌����𐮗񂷂鑀�Ǘ͂�Ԃ�
DirectX::SimpleMath::Vector3 SteeringBehavior::Alignment()
{
	using namespace DirectX::SimpleMath;

	// �C���̕������a�x�N�g��
	Vector3 headingSum = Vector3::Zero;
	// �C���̕������σx�N�g��
	Vector3 HeadingAverage = Vector3::Zero;
	// �ߐڌ̐����J�E���g����
	int neighborCount = 0;
	// �����x�N�g���̑��a���v�Z����  
	for (int index = 0; index < m_neighbors.size(); index++)
	{
		// �����x�N�g���̑��a���v�Z����
		headingSum += m_neighbors[index]->GetHeading();
		// �̂̃J�E���g����
		neighborCount++;
	}
	// �����x�N�g���𕽋ω�����
	if (neighborCount > 0)
	{
		// �������a�x�N�g���̕��ς��v�Z����
		HeadingAverage = headingSum / (float)neighborCount;
		// �������σx�N�g�����玩�C���̌��������炷
		HeadingAverage -= m_turret->GetHeading();
	}
	// �����x�N�g���̕��ϒl��Ԃ�
	return HeadingAverage;
}

// ��Q�����������
DirectX::SimpleMath::Vector3 SteeringBehavior::ObstacleAvoidance(const DirectX::SimpleMath::Vector3& targetPosition)
{
	using namespace DirectX::SimpleMath;

	// ��Q���ւ̋���
	const float OBSTACLE_DISTANCE = 100.0f;
	// ��Q���̔��a
	const float OBSTACLE_RADIUS = 30.0f;
	// �ő����
	const float MAX_AVOIDANCE_FORCE = 20.0f;

	// ���͂�錾����
	Vector3 avoidanceForce = Vector3::Zero;
	// �댯�x�X�R�A�̍ő�l��錾����
	float highestDangerScore = 0.0f;
	// �ł��댯�ȏ�Q����錾����
	IComponent* mostDangerousObstacle = nullptr;  
	// �^�[�Q�b�g�ւ̃x�N�g�����v�Z����
	Vector3 toTarget = targetPosition - m_turret->GetPosition();
	// ���ׂĂ̏�Q���̒�����ł��댯�ȏ�Q��(�������Z���A�i�s�����ɋ߂���Q��)�����o����
	for (const auto& obstacle : NodeFactory::GetObstacles())
	{
		// ��Q���ւ̃|�C���^���v�Z����
		Vector3 toObstacle = obstacle->GetPosition() - m_turret->GetPosition();
		// ��Q���ւ̋������v�Z����
		float toObstacleDistance = toObstacle.Length();

		// ��Q��������������ɂ���A�i�s�����ɑ��݂���ꍇ
		if (toObstacleDistance < (OBSTACLE_DISTANCE + OBSTACLE_RADIUS) && toTarget.Dot(toObstacle) > 0)
		{
			// �C���̐i�s�����x�N�g�����v�Z����
			Vector3 turretHeading = m_turret->GetVelocity();
			// ���K������
			turretHeading.Normalize();
			// ���ۂ̋������v�Z����
			float actualDistance = toObstacleDistance - OBSTACLE_RADIUS;
			// �����̋t����p���Ċ댯�x�X�R�A���v�Z����
			float distanceScore = 1.0f / std::max(actualDistance, 1.0f);
			// �C���̐i�s�����Ə�Q���̕����̊p�x�Ɋ�Â��댯�x�X�R�A���v�Z����
			float angleScore = turretHeading.Dot(toObstacle) / toObstacle.Length();
			// �����I�Ȋ댯�x�X�R�A���v�Z
			float dangerScore = distanceScore * angleScore;

			// �댯�x������܂łōő�Ȃ�A�ł��댯�ȏ�Q���Ƃ��ċL�^����
			if (dangerScore > highestDangerScore) 
			{
				// �ł��댯�ȃX�R�A��ݒ肷��
				highestDangerScore = dangerScore;
				// �ł��댯�ȏ�Q����ݒ肷��
				mostDangerousObstacle = obstacle;
			}
		}
	}

	// �ł��댯�ȏ�Q���ɑ΂��ĉ��͂�K�p����
	if (mostDangerousObstacle)
	{
		// ��Q���ւ̃x�N�g�����v�Z����
		Vector3 toObstacle = mostDangerousObstacle->GetPosition() - m_turret->GetPosition();
		// �C���̌�����ݒ肷��
		Vector3 turretHeading = m_turret->GetVelocity();
		// ���K������
		turretHeading.Normalize();
		// �C���̌����Ə�Q���Ƃ̊O�ς��v�Z����
		Vector3 crossProduct = turretHeading.Cross(toObstacle);
		// ���E�𔻒肷��
		float sideSign = crossProduct.y > 0.0f ? 1.0f : -1.0f;
		// �������̉�����v�Z����
		Vector3 sideAvoidance = turretHeading.Cross(Vector3::UnitY) * sideSign;
		// �����Ɋ�Â��ĉ��͂��v�Z���A�댯�x�X�R�A�𔽉f����
		float distanceFactor = pow((OBSTACLE_DISTANCE + OBSTACLE_RADIUS) / toObstacle.Length(), 2.0f);
		// ���͂��v�Z����
		avoidanceForce = sideAvoidance * distanceFactor * highestDangerScore;
	}

	// ���͂̏����K�p����
	if (avoidanceForce.Length() > MAX_AVOIDANCE_FORCE) 
	{
		// ���͂𐳋K������
		avoidanceForce.Normalize();
		// ���͂��ő剻����
		avoidanceForce *= MAX_AVOIDANCE_FORCE;
	}
	// ���͂�Ԃ�
	return avoidanceForce;
}

