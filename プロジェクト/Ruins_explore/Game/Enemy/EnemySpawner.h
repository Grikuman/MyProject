/*
	@file	EnemySpawner.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class SmallEnemy;
class Collision;

namespace NRLib
{
	class TPS_Camera;
}

// 一般的なシーンクラス
class EnemySpawner
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	NRLib::TPS_Camera* m_camera; // カメラオブジェクトへのポインタ

	// 小型エネミー
	static const int MAX_SMALL_ENEMY = 2;                        // 小型エネミー生成数
	std::unique_ptr<SmallEnemy> m_smallEnemy[MAX_SMALL_ENEMY];   // 小型エネミー
	// 当たり判定
	std::unique_ptr<Collision> m_collision;

public:
	EnemySpawner();
	~EnemySpawner();

	void Initialize(CommonResources* resources, NRLib::TPS_Camera* camera);
	void Update(DirectX::BoundingSphere boundingSphere,bool isAttack);
	void Render();
	void Finalize();
public:
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }
};
