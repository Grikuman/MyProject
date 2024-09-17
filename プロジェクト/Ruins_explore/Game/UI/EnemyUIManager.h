/*
	@file	EnemyUIManager.h
	@brief	プレイヤーのUIを管理するクラス
*/
#pragma once
#include "EnemyUIManager.h"
#include "Gauge.h"

class EnemyUIManager
{
public:
	// コンストラクタ
	EnemyUIManager();
	// デストラクタ
	~EnemyUIManager();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// ボスの体力ゲージ
	std::unique_ptr<tito::Gauge> m_gauge;
};
