/*
	@file	Field.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class GeometricPrimitive;

namespace NRLib
{
	class TPS_Camera;
}

// 一般的なシーンクラス
class Field
{
private:
	// 共通リソース
	CommonResources* m_commonResources;
	// 敵のモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_box[2];
	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder[3];
	// 敵の座標
	DirectX::SimpleMath::Vector3 m_boxPos[2];
	DirectX::SimpleMath::Vector3 m_cylinderPos[3];
	// カメラのポインタ
	NRLib::TPS_Camera* m_camera;

public:
	Field();
	~Field();

	void Initialize(CommonResources* resources,NRLib::TPS_Camera* camera);
	void Update();
	void Render();
	void Finalize();
};
