/*
	@file	Sky.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;

namespace mylib
{
	class DebugCamera;
}

// 一般的なシーンクラス
class Sky
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// デバッグカメラ
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;


	// ★以下、追記する変数など★

	// モデルの描画で使用する
	std::unique_ptr<DirectX::Model> m_model;	// モデル


public:
	Sky();
	~Sky();

	void Initialize(CommonResources* resources);
	void Update();
	void Render();
	void Finalize();
};
