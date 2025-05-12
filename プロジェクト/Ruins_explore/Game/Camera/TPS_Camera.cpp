/*
	ファイル名：TPS_Camera.cpp
	　　　概要：三人称カメラを制御するクラス
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Framework/EventMessenger.h"

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
NRLib::TPS_Camera::TPS_Camera(const DirectX::SimpleMath::Vector3& target)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ target },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_isShaking{false},
	m_shakeIntensity{},
	m_shakeDuration{},
	m_shakeOffset{}
{
	CalculateEyePosition(DirectX::SimpleMath::Matrix::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
	// イベントを登録する
	RegisterEvent();
}

//-------------------------------------------------------------------
// イベントを登録する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::RegisterEvent()
{
	// カメラ振動をイベント登録する
	EventMessenger::Attach(
		EventList::ShakeCamera, std::bind(&NRLib::TPS_Camera::ShakeCamera, this, std::placeholders::_1));
}

//-------------------------------------------------------------------
// 初期化する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::Initialize()
{
	// イベントを登録する
	RegisterEvent();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::Update(
	const DirectX::SimpleMath::Vector3& newTarget,
	const DirectX::SimpleMath::Matrix& rotate
)
{
	// targetの位置を更新する
	//m_target = newTarget;	// バネなし
	m_target += (newTarget - m_target) * 0.05f;	// バネ付き

	// カメラ座標を計算する
	CalculateEyePosition(rotate);

	// カメラ揺れの適用
	if (m_isShaking)
	{
		// ランダムな揺れを加える
		m_shakeOffset.x = ((rand() % 100) / 50.0f - 1.0f) * m_shakeIntensity;
		m_shakeOffset.y = ((rand() % 100) / 50.0f - 1.0f) * m_shakeIntensity;
		m_shakeOffset.z = ((rand() % 100) / 50.0f - 1.0f) * m_shakeIntensity;

		// 揺れが終了したらフラグをリセット
		m_shakeDuration -= 0.016f; // フレームごとに減らす（約60FPS）
		if (m_shakeDuration <= 0.0f)
		{
			m_isShaking = false;
			m_shakeOffset = DirectX::SimpleMath::Vector3::Zero;
		}
	}

	// ビュー行列を更新する
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::CalculateViewMatrix()
{
	// カメラ位置に揺れを加える
	DirectX::SimpleMath::Vector3 shakePosition = m_eye + m_shakeOffset;

	// ビュー行列を更新
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(shakePosition, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::CalculateProjectionMatrix()
{
	// ウィンドウサイズ
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// 画面縦横比
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void NRLib::TPS_Camera::CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate)
{
	// カメラのデフォルトの座標ベクトル
	DirectX::SimpleMath::Vector3 eye{ 0.0f, CAMERA_HIGHT, CAMERA_DISTANCE };
	// ターゲットの向いている方向に追従する
	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotate);
	// カメラ座標を計算する
	m_eye += (m_target + eye - m_eye) * 0.05f;
	// x, z 座標を -20 から 20 の範囲に制限
	m_eye.x = std::max(-30.0f, std::min(m_eye.x, 30.0f));
	m_eye.z = std::max(-30.0f, std::min(m_eye.z, 30.0f));
}

//-------------------------------------------------------------------
// ダメージを受けたときのカメラ揺れ処理を開始
//-------------------------------------------------------------------
void NRLib::TPS_Camera::StartShake(float intensity, float duration)
{
	m_isShaking = true;
	m_shakeIntensity = intensity;
	m_shakeDuration = duration;
}

//-------------------------------------------------------------------
// カメラを振動させる(イベント登録用)
//-------------------------------------------------------------------
void NRLib::TPS_Camera::ShakeCamera(void* args)
{
	// 引数をpairで分割できるようにする
	auto pair = static_cast<std::pair<float, float>*>(args);
	// カメラの振動処理
	StartShake(pair->first, pair->second);
}

