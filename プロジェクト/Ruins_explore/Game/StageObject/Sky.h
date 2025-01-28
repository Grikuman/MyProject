/*
	ファイル名：Sky.h
	　　　概要：空を表示するクラス
*/
#pragma once

// 一般的なシーンクラス
class Sky
{
public:
	// コンストラクタ
	Sky();
	// デストラクタ
	~Sky();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 終了処理
	void Finalize();
private:
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// モデルの描画で使用する
	std::unique_ptr<DirectX::Model> m_model;

	// 回転カウント
	float m_rotateCnt;
};
