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

// AABB���m�̏Փ˔���
bool Collision::CheckCollision(DirectX::BoundingSphere box1, DirectX::BoundingSphere box2)
{
	return box1.Intersects(box2);
}
