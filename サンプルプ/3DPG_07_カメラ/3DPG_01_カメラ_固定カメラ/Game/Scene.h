/*
	@file	Scene.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;

namespace mylib
{
	class GridFloor;
	class FixedCamera;
}

// 一般的なシーンクラス
class Scene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;


	// ★以下、追記する変数など★

	// モデルの描画で使用する
	std::unique_ptr<DirectX::Model> m_model;	// モデル
	float							m_angle;	// 回転角（度）

	std::unique_ptr<mylib::FixedCamera> m_camera;	// 固定カメラ


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
};
