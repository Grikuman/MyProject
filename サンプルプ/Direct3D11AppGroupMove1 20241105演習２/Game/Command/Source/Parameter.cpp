#include "Framework/pch.h"
#include "Command/Header/Parameter.h"

// コンストラクタ
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

// コンストラクタ
Parameter::Parameter(const float& distance, const float& angle)
	:
	// 位置
	m_distance(distance),
	// 回転角
	m_angle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(angle))),
	m_startPosition{},
	m_endPosition{},
	m_currentPosition{},
	m_startAngle{},
	m_endAngle{},
	m_currentAngle{}
{
}

// 水平終了位置を計算する
void Parameter::CalculateEndPositionH(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle)
{
	// 水平終了位置を計算する
	m_endPosition = position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, m_distance), angle);
}

// 水平終了位置を計算する
void Parameter::CalculateEndPositionV(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle)
{
	// 水平終了位置を計算する
	m_endPosition = position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, m_distance, 0.0f), angle);
}
