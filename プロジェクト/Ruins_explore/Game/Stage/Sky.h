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
	// カメラの画角
	const float FIELD_OF_VIEW = 45.0f;
	// カメラの近クリップ面
	const float NEAR_PLANE = 0.1f;
	// カメラの遠クリップ面
	const float FAR_PLANE = 1000.0f;
	// 画面の幅
	const float SCREEN_WIDTH = 1280.0f;
	// 画面の高さ
	const float SCREEN_HEIGHT = 720.0f;

	// 回転の速さ
	const float ROTATE_SPEED = 0.05f;
	// 天球の向き調整(X軸)
	const float ROTATE_X = 180.f;

private:
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	// モデル
	DirectX::Model* m_model;
	// 回転カウント
	float m_rotateCnt;
};
