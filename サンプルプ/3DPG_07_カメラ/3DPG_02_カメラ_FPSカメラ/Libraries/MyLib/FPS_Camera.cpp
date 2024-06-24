/*
	@file	FPS_Camera.cpp
	@brief	FPSカメラクラス
*/
#include "pch.h"
#include "FPS_Camera.h"
#include "Game/Screen.h"

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
mylib::FPS_Camera::FPS_Camera(
	const DirectX::SimpleMath::Vector3& eye,
	const DirectX::SimpleMath::Vector3& target,
	const DirectX::SimpleMath::Vector3& up
)
	:
	m_view{},
	m_projection{},
	m_eye{ eye },
	m_target{ target },
	m_up{ up }
{
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//-------------------------------------------------------------------
// 更新する
//-------------------------------------------------------------------
void mylib::FPS_Camera::Update(const DirectX::SimpleMath::Vector3& newEye)
{
	// 古いeyeを保持する
	DirectX::SimpleMath::Vector3 oldEye = m_eye;

	// eyeの位置を更新する
	m_eye = newEye;

	// 移動ベクトルを求める
	DirectX::SimpleMath::Vector3 velocity = m_eye - oldEye;

	// targetの位置を更新する
	m_target += velocity;

	// ビュー行列を更新する
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// ビュー行列を計算する
//-------------------------------------------------------------------
void mylib::FPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// プロジェクション行列を計算する
//-------------------------------------------------------------------
void mylib::FPS_Camera::CalculateProjectionMatrix()
{
	// ウィンドウサイズ
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// 画面縦横比
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}
