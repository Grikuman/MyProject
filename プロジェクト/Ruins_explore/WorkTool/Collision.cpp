//*=======================================================*
// Collision.cpp
//*=======================================================*
#include "pch.h"
#include "WorkTool/Collision.h"
using namespace DirectX;

bool Collision::CheckGround(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 ground)
{
	//プレイヤー座標が地面にあたっていたらtrueを返す
	if (position.y <= ground.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// AABB同士の衝突判定
bool Collision::CheckCollision(DirectX::BoundingSphere box1, DirectX::BoundingSphere box2)
{
	return box1.Intersects(box2);
}
