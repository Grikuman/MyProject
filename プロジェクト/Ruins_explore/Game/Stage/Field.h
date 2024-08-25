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
	// ステージのモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// ステージの座標
	DirectX::SimpleMath::Vector3 m_boxPos;
	// カメラのポインタ
	NRLib::TPS_Camera* m_camera;
	// バウンディングボックスの格納用
	std::vector<DirectX::BoundingBox> m_vBoundingBox;

public:
	Field();
	~Field();

	void Initialize(CommonResources* resources,NRLib::TPS_Camera* camera);
	void Update();
	void Render();
	void Finalize();
	std::vector<DirectX::BoundingBox> GetFieldCollision();

private:
	std::unique_ptr<DirectX::Model> m_pyramid;

};
