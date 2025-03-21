#include "Framework/pch.h"
#include "Camera.h"

// コンストラクタ
Camera::Camera(const DirectX::SimpleMath::Vector3& targetPosition, const DirectX::SimpleMath::Vector3& eyePoaition)
	:
	m_eyePosition(eyePoaition),		// 視点の位置
	m_targetPosition(targetPosition)		// 注視点の位置
{
}

// デストラクタ
Camera::~Camera()
{
}

// ビュー行列を更新する
void Camera::Update()
{
	// カメラのUPベクトルを計算する
	DirectX::SimpleMath::Vector3 toEye = GetEyePosition() - GetTargetPosition();
	// 正規化する
	toEye.Normalize();
	// UPベクトルを計算する
	DirectX::SimpleMath::Vector3 up = toEye.Cross(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f));
	// ビュー行列を生成する
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt(GetEyePosition(), GetTargetPosition(), up	);
	// ビュー行列を設定する
	Graphics::GetInstance()->SetViewMatrix(view);
}
