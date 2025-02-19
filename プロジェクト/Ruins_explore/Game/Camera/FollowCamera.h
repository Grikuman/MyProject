/*
	@file	FollowCamera.h
	@brief	後追いカメラクラス、ばね付き
*/
#pragma once

class FollowCamera
{
public:
	// カメラの視点位置を取得する
	const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }
	// カメラの注視点（ターゲットの位置）を取得する
	const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

public:
	// コンストラクタ
	FollowCamera();
	// デストラクタ
	~FollowCamera() = default;
	// 初期化する
	void Initialize(
		const DirectX::SimpleMath::Vector3* followUpTargetPosition,
		const DirectX::SimpleMath::Quaternion* followUpTargetQuaternion
	);
	// 更新する
	void Update();

private:
	// バネレート
	static constexpr float SPRING_RATE_EYE = 0.05f;
	static constexpr float SPRING_RATE_TARGET = 0.05f;
	// 距離、高さ
	static constexpr float DISTANCE = 5.0f;
	static constexpr float HEIGHT = 3.0f;

	// カメラ座標
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	// 追跡対象の座標のポインタ（参照先を更新不可とする）
	const DirectX::SimpleMath::Vector3* m_followUpTargetPosition;

	// 追跡対象のクォータニオンのポインタ（参照先を更新不可とする）
	const DirectX::SimpleMath::Quaternion* m_followUpTargetQuaternion;
};
