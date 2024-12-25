#include "Framework/pch.h"
#include "Command/Header/Parameter.h"

// �R���X�g���N�^
Parameter::Parameter()
	:
	m_startPosition{},
	m_currentPosition{},
	m_endPosition{},
	m_distance{},
	m_startAngle{},
	m_currentAngle{},
	m_endAngle{},
	m_angle{}
{
}

// �R���X�g���N�^
Parameter::Parameter(const float& distance, const float& angle)
	:
	// �ʒu
	m_distance(distance),
	// ��]�p
	m_angle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(angle))),
	m_startPosition{},
	m_endPosition{},
	m_currentPosition{},
	m_startAngle{},
	m_endAngle{},
	m_currentAngle{}
{
}

// �����I���ʒu���v�Z����
void Parameter::CalculateEndPositionH(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle)
{
	// �����I���ʒu���v�Z����
	m_endPosition = position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, m_distance), angle);
}

// �����I���ʒu���v�Z����
void Parameter::CalculateEndPositionV(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle)
{
	// �����I���ʒu���v�Z����
	m_endPosition = position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, m_distance, 0.0f), angle);
}
