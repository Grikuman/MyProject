#pragma once
#ifndef IFACTORY_METHOD_DEFINED
#define IFACTORY_METHOD_DEFINED
#include "Interface/IComponent.h"

// –C“ƒƒtƒ@ƒNƒgƒŠƒCƒ“ƒ^ƒtƒF[ƒX‚ğ’è‹`‚·‚é
class ITurretFactory
{
public:
	// –C“ƒ‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒ‰º•”‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒ’†•”‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒã•”‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒ–C‘ä‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒ–Cg‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒƒvƒŒ[ƒg‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// –C“ƒ‹r‚ğ¶¬‚·‚é
	virtual std::unique_ptr<IComponent> CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
};

#endif		// FACTORY_METHOD_DEFINED
