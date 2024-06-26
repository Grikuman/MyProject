/*
	@file	SmallEnemy.h
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
class SmallEnemy
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	NRLib::TPS_Camera* m_camera; // カメラオブジェクトへのポインタ

	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;

	DirectX::SimpleMath::Vector3 m_position; // 座標
public:
	SmallEnemy();
	~SmallEnemy();

	void Initialize(CommonResources* resources, NRLib::TPS_Camera* camera, DirectX::SimpleMath::Vector3 position);
	void Update();
	void Render();
	void Finalize();
public:
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }
};
