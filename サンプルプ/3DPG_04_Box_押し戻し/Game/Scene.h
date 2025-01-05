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

	//// ベーシックエフェクト
	//std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	//// プリミティブバッチ
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	//// 入力レイアウト
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// デバッグカメラ
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;
	
	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;


	// ★以下、追記する変数など★

	// ジオメトリックプリミティブ
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// 回転角（度）
	float m_angle;
	// 座標
	DirectX::SimpleMath::Vector3 m_positionA;
	DirectX::SimpleMath::Vector3 m_positionB;
	// 速さ
	static constexpr float SPEED = 0.05f;
	// ヒットフラグ
	bool m_isHit;
	// バウンディングボックス
	DirectX::BoundingBox m_boundingBoxA;
	DirectX::BoundingBox m_boundingBoxB;

public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();

private:
	// 衝突判定
	void CheckHit();
};
