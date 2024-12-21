/*
	ファイル名：Sky.h
	　　　概要：空を表示するクラス
*/
#pragma once

// 前方宣言
class GeometricPrimitive;

// 一般的なシーンクラス
class Field
{
public:
	// コンストラクタ
	Field();
	// デストラクタ
	~Field();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 終了処理
	void Finalize();
private:
	// ステージのモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// ステージの座標
	DirectX::SimpleMath::Vector3 m_boxPos;

private:
	std::unique_ptr<DirectX::Model> m_pyramid;

};
