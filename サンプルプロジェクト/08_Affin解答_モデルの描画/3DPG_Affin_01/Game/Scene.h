/*
	@file	Scene.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

// 一般的なシーンクラス
class Scene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// デバッグカメラ
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;
	
	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	// 回転
	float m_rotation;

	// フレームカウンタ
	unsigned int m_frameCounter;

	// サイコロの配列
	DirectX::SimpleMath::Vector3 m_positions[8];


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
