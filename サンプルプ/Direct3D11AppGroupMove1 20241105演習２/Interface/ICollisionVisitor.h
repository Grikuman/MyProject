#pragma once
#ifndef ICOLLISION_VISITOR_DEFINED
#define ICOLLISION_VISITOR_DEFINED
#include "Interface/IBullet.h"

class ICollisionVisitor
{
public:
	// デストラクタ
	virtual ~ICollisionVisitor() = default;

	// 衝突準備ビジターを開始する
	virtual void StartPrepareCollision(IComponent* component) = 0;
	// 再帰的に衝突準備ビジターを呼び出す
	virtual void PrepareCollision(IComponent* component) = 0;
	// 再帰的にDetectCollision関数を呼び出す
	virtual void DetectCollision(IComponent* component, IBullet* bullets) = 0;
	// 境界ボックスを描画する
	virtual void DrawBoundingBox(int index, const DirectX::SimpleMath::Matrix& matrix) = 0;
	// ノード番号から砲塔部品にカラーを設定する
	virtual void SetTurretPartColor(int nodeNumber, DirectX::Model* model, bool collision) = 0;
	// モデルにカラーを設定する
	virtual void SetColorToModel(DirectX::Model* model, const DirectX::XMVECTORF32& color) = 0;
};

#endif		// ICOLLISION_VISITOR_DEFINED
