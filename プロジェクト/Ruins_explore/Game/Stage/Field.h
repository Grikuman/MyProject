/*
	@file	Field.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class GeometricPrimitive;

// 一般的なシーンクラス
class Field
{
private:
	// ステージのモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// ステージの座標
	DirectX::SimpleMath::Vector3 m_boxPos;

public:
	Field();
	~Field();

	void Initialize();
	void Update();
	void Render();
	void Finalize();

private:
	std::unique_ptr<DirectX::Model> m_pyramid;

};
