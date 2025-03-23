#pragma once
#ifndef ICOLLISION_DEFINED
#define ICOLLISION_DEFINED
#include "Interface/ICollisionVisitor.h"

class ICollision
{
public:
	// Õ“Ë”»’è‚ğ€”õ‚·‚é
	virtual void PrepareCollision(ICollisionVisitor* collision) = 0;
	// Õ“Ë”»’è‚·‚é
	virtual void DetectCollision(ICollisionVisitor* collision, IBullet* bullets) = 0;
};

#endif			// ICOLLISION_DEFINED

