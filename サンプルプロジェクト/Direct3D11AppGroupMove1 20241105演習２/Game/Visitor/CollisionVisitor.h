#pragma once
#ifndef COLLISION_VISITOR_DEFINED
#define COLLISION_VISITOR_DEFINED
#include "Interface/IComponent.h"

class CollisionVisitor : public ICollisionVisitor
{
public:
	// CollisionVisitorクラスのインスタンスを取得する
	static CollisionVisitor* GetInstance();
	// コンストラクタ
	CollisionVisitor();
	// デストラクタ
	~CollisionVisitor();
	// 衝突判定を開始する
	void StartPrepareCollision(IComponent* component);
	// 衝突判定の準備を行う
	void PrepareCollision(IComponent* component);
	// 衝突判定を行う
	void DetectCollision(IComponent* component, IBullet* bullet);
	// 境界ボックスを描画する
	void DrawBoundingBox(int index, const DirectX::SimpleMath::Matrix& matrix);
	// ノード番号から砲塔部品にカラーを設定する
	void SetTurretPartColor(int nodeNumber, DirectX::Model* model, bool collision);
	// モデルにカラーを設定する
	void SetColorToModel(DirectX::Model* model, const DirectX::XMVECTORF32& color);


private:
	// コリジョンビジター
	static std::unique_ptr<CollisionVisitor> s_collisionVisitor;
	// グラフィックス
	Graphics* m_graphics;
	// 「砲塔」配列バウンディングボックス
	std::unordered_map<int, DirectX::BoundingBox> m_boundingBoxes;
	// ワールド行列配列
	std::vector<DirectX::SimpleMath::Matrix*> m_worldMatrixes;

};

#endif		// COLLISION_VISITOR_DEFINED
