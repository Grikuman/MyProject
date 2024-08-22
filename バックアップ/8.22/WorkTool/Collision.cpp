//*=======================================================*
// Collision.cpp
//*=======================================================*
#include "pch.h"
#include "WorkTool/Collision.h"
using namespace DirectX;

bool Collision::CheckGround(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 ground)
{
	//�v���C���[���W���n�ʂɂ������Ă�����true��Ԃ�
	if (position.y <= ground.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ���̓��m�̏Փ˔���
bool Collision::SphereIntersects(DirectX::BoundingSphere sphere1, DirectX::BoundingSphere sphere2)
{
	return sphere1.Intersects(sphere2);
}
