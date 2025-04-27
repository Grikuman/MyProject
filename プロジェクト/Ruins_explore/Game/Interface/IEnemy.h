/*
	ファイル名：IEnemy.h
	　　　概要：敵のインターフェース
*/
#pragma once
#include "ICollisionObject.h"

class IEnemy : public ICollisionObject
{
public:
	// 生存しているか
	virtual bool IsAlive() const = 0;
	// バウンディングボックスを取得する
	virtual DirectX::BoundingBox GetBoundingBox() const = 0;

public:
	// デストラクタ
	virtual ~IEnemy() = default;
	// 初期化する
	virtual void Initialize(DirectX::SimpleMath::Vector3 position) = 0;
	// 更新する
	virtual void Update() = 0;
	// 描画する
	virtual void Render() = 0;
	// 終了処理
	virtual void Finalize() = 0;
};