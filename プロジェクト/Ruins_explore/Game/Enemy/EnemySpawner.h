/*
	@file	EnemySpawner.h
	@brief	一般的なシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class Tunomaru;
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
	// カメラオブジェクトへのポインタ
	NRLib::TPS_Camera* m_camera;
	// 生存している敵の数
	int m_aliveEnemy;
	// つのまるの数
	static const int MAX_TUNOMARU = 2;
	// つのまる
	std::unique_ptr<Tunomaru> m_tunomaru[MAX_TUNOMARU];
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
	// カメラを設定する
	void SetCamera(NRLib::TPS_Camera* camera) { m_camera = camera; }
};
