/*
	ファイル名：.h
	　　　概要：を管理するクラス
*/
#pragma once

class ChargePunch
{
public:
	// コンストラクタ
	ChargePunch();
	// デストラクタ
	~ChargePunch();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(float elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();
};
