#pragma once
#ifndef PARAMETER_DEFINED
#define PARAMETER_DEFINED

class Parameter
{
public:
	// 開始位置を取得する
	DirectX::SimpleMath::Vector3 GetStartPosition() const { return m_startPosition; }
	// 開始位置を設定する
	void SetStartPosition(const DirectX::SimpleMath::Vector3& startPosition) { m_startPosition = startPosition; }
	// 終了位置を取得する
	DirectX::SimpleMath::Vector3 GetEndPosition() const { return m_endPosition; }
	// 終了位置を設定する
	void SetEndPosition(const DirectX::SimpleMath::Vector3& endPosition) { m_endPosition = endPosition; }
	// 現在の位置を取得する
	DirectX::SimpleMath::Vector3 GetCurrentPosition() const { return m_currentPosition; }
	// 現在の位置を設定する
	void SetCurrentPosition(const DirectX::SimpleMath::Vector3& currentPosition) { m_currentPosition = currentPosition; }
	// 移動距離を取得する
	float GetDistance() const { return m_distance; }

	// 開始角度を取得する
	DirectX::SimpleMath::Quaternion GetStartAngle() const { return m_startAngle; }
	// 開始角度を設定する
	void SetStartAngle(const DirectX::SimpleMath::Quaternion& startAngle) { m_startAngle = startAngle; }
	// 終了角度を取得する
	DirectX::SimpleMath::Quaternion GetEndAngle() const { return m_endAngle; }
	// 終了角度を設定する
	void SetEndAngle(const DirectX::SimpleMath::Quaternion endAngle) { m_endAngle = endAngle; }
	// 現在の角度を取得する
	DirectX::SimpleMath::Quaternion GetCurrentAngle() const { return m_currentAngle; }
	// 現在の角度を設定する
	void SetCurrentAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// 回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }

public:
	// コンストラクタ
	Parameter();
	// コンストラクタ
	Parameter(const float& distance, const float& angle	);
	// 水平終了位置を計算する
	void CalculateEndPositionH(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle);
	// 水平終了位置を計算する
	void CalculateEndPositionV(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion angle);

private:
	// 現在位置
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 開始位置
	DirectX::SimpleMath::Vector3 m_startPosition;
	// 終了位置
	DirectX::SimpleMath::Vector3 m_endPosition;
	// 距離
	float m_distance;

	// 現在角度
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// 開始回転角
	DirectX::SimpleMath::Quaternion m_startAngle;
	// 終了回転角
	DirectX::SimpleMath::Quaternion m_endAngle;
	// 回転角
	DirectX::SimpleMath::Quaternion m_angle;
};

#endif		// PARAMETER_DEFINED
