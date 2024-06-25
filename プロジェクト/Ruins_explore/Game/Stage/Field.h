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

	std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;

	NRLib::TPS_Camera* m_camera; // カメラオブジェクトへのポインタ

public:
	Field();
	~Field();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
public:
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }
};
