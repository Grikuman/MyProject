#pragma once
#ifndef TURRETFACTORY_DEFINED
#define TURRETFACTORY_DEFINED
#include "Interface/IComponent.h"
#include "Interface/ITurretFactory.h"

// –C“ƒƒtƒ@ƒNƒgƒŠƒNƒ‰ƒX‚ğ’è‹`‚·‚é
class TurretFactory : public ITurretFactory
{
public:
	// –C“ƒ‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒ‰º•”‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒ’†•”‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒã•”‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒ–C‘ä‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒ–Cg‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒƒvƒŒ[ƒg‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// –C“ƒ‹r‚ğ¶¬‚·‚é
	static std::unique_ptr<IComponent> CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
};

#endif		// TURRETFACTORY_DEFINED