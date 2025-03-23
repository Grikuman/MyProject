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

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	// クォータニオン：モデルの回転を制御する
	DirectX::SimpleMath::Quaternion m_rotate;

	// モデルの座標
	DirectX::SimpleMath::Vector3 m_position;


public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
