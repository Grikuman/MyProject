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

// 球体同士の衝突判定
bool Collision::SphereIntersects(DirectX::BoundingSphere sphere1, DirectX::BoundingSphere sphere2)
{
	return sphere1.Intersects(sphere2);
}
