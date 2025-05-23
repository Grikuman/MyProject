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
		// イベントを登録する
		void RegisterEvent();
		// 初期化する
		void Initialize();
		// 更新処理
		void Update(const DirectX::SimpleMath::Vector3& newTarget,const DirectX::SimpleMath::Matrix& rotate);
		// ダメージを受けたときのカメラ揺れ処理を開始
		void StartShake(float intensity, float duration);
		// カメラを振動させる
		void ShakeCamera(void* args);

	private:
		// ビュー行列を計算する
		void CalculateViewMatrix();
		// プロジェクション行列を計算する
		void CalculateProjectionMatrix();
		// カメラ座標を計算する 
		void CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate);

	private:
		// ターゲットからのデフォルト距離
		const float CAMERA_DISTANCE = 7.0f;
		const float CAMERA_HIGHT = 1.0f;
		// 画角
		const float FOV = DirectX::XMConvertToRadians(55.0f);
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

		// ダメージ時のカメラ揺れの状態管理
		bool m_isShaking;
		// カメラ揺れの強さ
		float m_shakeIntensity;
		// カメラ揺れの残り時間
		float m_shakeDuration;
		// カメラ揺れのオフセット
		DirectX::SimpleMath::Vector3 m_shakeOffset;
	};
}
