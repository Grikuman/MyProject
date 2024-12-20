/*
	@file	
	@brief	
*/
#pragma once
#include "ICollisionObject.h"

class IEnemy : public ICollisionObject
{
public:
	virtual ~IEnemy() = default;
	// ‰Šú‰»‚·‚é
	virtual void Initialize(DirectX::SimpleMath::Vector3 position) = 0;
	// XV‚·‚é
	virtual void Update() = 0;
	// •`‰æ‚·‚é
	virtual void Render() = 0;
	// Œãˆ—‚ğs‚¤
	virtual void Finalize() = 0;
};