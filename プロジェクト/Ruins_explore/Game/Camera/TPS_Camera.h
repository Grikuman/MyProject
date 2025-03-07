/*
	ファイル名：TPS_Camera.h
	　　　概要：三人称カメラを制御するクラス
*/
#pragma once

namespace NRLib
{
	class TPS_Camera
	{
	public:
		// ビューを取得する
		const DirectX::SimpleMath::Matrix& GetViewMatrix() const       { return m_view; }
		// プロジェクションを取得する
		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
		// アイポジションを取得する
		const DirectX::SimpleMath::Vector3& GetEyePosition() const     { return m_eye; }
		// ターゲットを取得する
		const DirectX::SimpleMath::Vector3& GetTargetPosition() const  { return m_target; }
		// アップを取得する
		const DirectX::SimpleMath::Vector3& GetUpVector() const        { return m_up; }

	public:
		// コンストラクタ
		TPS_Camera(const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero);
		// デストラクタ
		~TPS_Camera() = default;
		// 更新処理
		void Update(const DirectX::SimpleMath::Vector3& newTarget,const DirectX::SimpleMath::Matrix& rotate);

	private:
		// ビュー行列を計算する
		void CalculateViewMatrix();
		// プロジェクション行列を計算する
		void CalculateProjectionMatrix();
		// カメラ座標を計算する
		void CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate);

	private:
		// ターゲットからのデフォルト距離
		const float CAMERA_DISTANCE = 15.0f;
		const float CAMERA_HIGHT = 3.5f;
		// 画角
		const float FOV = DirectX::XMConvertToRadians(45.0f);
		// 近い投影面
		const float NEAR_PLANE = 1.0f;
		// 遠い投影面
		const float FAR_PLANE = 1000.0f;

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
}
