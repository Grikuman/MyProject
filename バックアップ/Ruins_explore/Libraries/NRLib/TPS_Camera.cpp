/*
	@file	TPS_Camera.cpp
	@brief	TPSカメラクラス、ばね付き
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
NRLib::TPS_Camera::TPS_Camera(const DirectX::SimpleMath::Vector3& target)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ target },
	m_up{ DirectX::SimpleMath::Vector3::UnitY }
{
	CalculateEyePosition(DirectX::SimpleMath::Matrix::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::Update(
	const DirectX::SimpleMath::Vector3& newTarget,
	const DirectX::SimpleMath::Matrix& rotate
)
{
	/*
		ToDo::追従カメラなので、引数はelapsedTimeだけにしたい
		→newTarget,rotateはカメラの内部的に計算したい
	*/

	// targetの位置を更新する
	//m_target = newTarget;	// バネなし
	m_target += (newTarget - m_target) * 0.05f;	// バネ付き

	// カメラ座標を計算する
	CalculateEyePosition(rotate);

	// ビュー行列を更新する
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
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

//-------------------------------------------------------------------
// カメラ座標を計算する
//-------------------------------------------------------------------
void NRLib::TPS_Camera::CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate)
{
	// カメラのデフォルトの座標ベクトル
	DirectX::SimpleMath::Vector3 eye{ 0.0f,CAMERA_HIGHT,CAMERA_DISTANCE };

	// ターゲットの向いている方向に追従する
	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotate);

	// カメラ座標を計算する
	//m_eye = m_target + eye;	// バネなし
	m_eye += (m_target + eye - m_eye) * 0.05f;	// バネ付き
}
