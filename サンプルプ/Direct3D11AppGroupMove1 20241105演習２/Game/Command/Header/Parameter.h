#pragma once
#ifndef PARAMETER_DEFINED
#define PARAMETER_DEFINED

class Parameter
{
public:
	// �J�n�ʒu���擾����
	DirectX::SimpleMath::Vector3 GetStartPosition() const { return m_startPosition; }
	// �J�n�ʒu��ݒ肷��
	void SetStartPosition(const DirectX::SimpleMath::Vector3& startPosition) { m_startPosition = startPosition; }
	// �I���ʒu���擾����
	DirectX::SimpleMath::Vector3 GetEndPosition() const { return m_endPosition; }
	// �I���ʒu��ݒ肷��
	void SetEndPosition(const DirectX::SimpleMath::Vector3& endPosition) { m_endPosition = endPosition; }
	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetCurrentPosition() const { return m_currentPosition; }
	// ���݂̈ʒu��ݒ肷��
	void SetCurrentPosition(const DirectX::SimpleMath::Vector3& currentPosition) { m_currentPosition = currentPosition; }
	// �ړ��������擾����
	float GetDistance() const { return m_distance; }

	// �J�n�p�x���擾����
	DirectX::SimpleMath::Quaternion GetStartAngle() const { return m_startAngle; }
	// �J�n�p�x��ݒ肷��
	void SetStartAngle(const DirectX::SimpleMath::Quaternion& startAngle) { m_startAngle = startAngle; }
	// �I���p�x���擾����
	DirectX::SimpleMath::Quaternion GetEndAngle() const { return m_endAngle; }
	// �I���p�x��ݒ肷��
	void SetEndAngle(const DirectX::SimpleMath::Quaternion endAngle) { m_endAngle = endAngle; }
	// ���݂̊p�x���擾����
	DirectX::SimpleMath::Quaternion GetCurrentAngle() const { return m_currentAngle; }
	// ���݂̊p�x��ݒ肷��
	void SetCurrentAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// ��]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }

public:
	// �R���X�g���N�^
	Parameter();
	// �R���X�g���N�^
	Parameter(const float& distance, const float& angle	);
	// �����I���ʒu���v�Z����
	void CalculateEndPositionH(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle);
	// �����I���ʒu���v�Z����
	void CalculateEndPositionV(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle);

private:
	// ���݈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// �J�n�ʒu
	DirectX::SimpleMath::Vector3 m_startPosition;
	// �I���ʒu
	DirectX::SimpleMath::Vector3 m_endPosition;
	// ����
	float m_distance;

	// ���݊p�x
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �J�n��]�p
	DirectX::SimpleMath::Quaternion m_startAngle;
	// �I����]�p
	DirectX::SimpleMath::Quaternion m_endAngle;
	// ��]�p
	DirectX::SimpleMath::Quaternion m_angle;
};

#endif		// PARAMETER_DEFINED
