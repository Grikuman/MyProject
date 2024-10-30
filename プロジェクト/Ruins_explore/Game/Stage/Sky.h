/*
	@file	Sky.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 一般的なシーンクラス
class Sky
{
private:
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// ★以下、追記する変数など★

	// モデルの描画で使用する
	std::unique_ptr<DirectX::Model> m_model;	// モデル


public:
	Sky();
	~Sky();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};
