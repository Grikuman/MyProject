#pragma once
#ifndef ICOLLISION_DEFINED
#define ICOLLISION_DEFINED
#include "Interface/ICollisionVisitor.h"

class ICollision
{
public:
	// �Փ˔������������
	virtual void PrepareCollision(ICollisionVisitor* collision) = 0;
	// �Փ˔��肷��
	virtual void DetectCollision(ICollisionVisitor* collision, IBullet* bullets) = 0;
};

#endif			// ICOLLISION_DEFINED

