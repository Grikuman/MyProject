//*=======================================================*
// Collision.cpp
//*=======================================================*
#include "pch.h"
#include "WorkTool/Collision.h"

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
