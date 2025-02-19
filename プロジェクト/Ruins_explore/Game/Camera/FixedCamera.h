/*
	ファイル名：FixedCamera.h
	　　　概要：固定カメラを制御するクラス
*/
#pragma once

class FixedCamera
{
public:
	// ビュー行列を取得する
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }
	// プロジェクション行列を取得する
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
	// カメラの視点位置を取得する（変更可能）
	DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eye; }
	// カメラの注視点（ターゲットの位置）を取得する（変更可能）
	DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	// カメラの上方向ベクトルを取得する
	const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }
	// カメラの視点位置を設定する
	void SetEyePosition(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }
	// カメラの注視点（ターゲットの位置）を設定する
	void SetTargetPosition(DirectX::SimpleMath::Vector3 target) { m_target = target; }

public:
	// コンストラクタ
	FixedCamera(
		DirectX::SimpleMath::Vector3& eye,
		DirectX::SimpleMath::Vector3& target,
		const DirectX::SimpleMath::Vector3& up = DirectX::SimpleMath::Vector3::UnitY);
	// デストラクタ
	~FixedCamera() = default;

private:
	// ビュー行列を計算する
	void CalculateViewMatrix();
	// プロジェクション行列を計算する
	void CalculateProjectionMatrix();

private:
	// 画角
	const float FOV = DirectX::XMConvertToRadians(45.0f);
	// 近い投影面
	const float NEAR_PLANE = 1.0f;
	// 遠い投影面
	const float FAR_PLANE = 100.0f;

private:
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projection;
	// カメラ座標
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// カメラの頭の方向
	DirectX::SimpleMath::Vector3 m_up;

};
