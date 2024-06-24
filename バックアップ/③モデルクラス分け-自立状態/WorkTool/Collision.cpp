//*=======================================================*
// Collision.cpp
//*=======================================================*
#include "pch.h"
#include "WorkTool/Collision.h"

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
