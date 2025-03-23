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

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;


	// ★以下、追記する変数など★

	// モデルの描画で使用する
	std::unique_ptr<DirectX::Model> m_model;	// モデル
	float							m_angle;	// 回転角（度）
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;	// ブレンドステート


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
};
