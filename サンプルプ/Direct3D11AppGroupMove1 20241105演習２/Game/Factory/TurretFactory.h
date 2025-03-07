#pragma once
#ifndef TURRETFACTORY_DEFINED
#define TURRETFACTORY_DEFINED
#include "Interface/IComponent.h"
#include "Interface/ITurretFactory.h"

// 砲塔ファクトリクラスを定義する
class TurretFactory : public ITurretFactory
{
public:
	// 砲塔を生成する
	static std::unique_ptr<IComponent> CreateTurret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔下部を生成する
	static std::unique_ptr<IComponent> CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔中部を生成する
	static std::unique_ptr<IComponent> CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔上部を生成する
	static std::unique_ptr<IComponent> CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔砲台を生成する
	static std::unique_ptr<IComponent> CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔砲身を生成する
	static std::unique_ptr<IComponent> CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔プレートを生成する
	static std::unique_ptr<IComponent> CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// 砲塔脚を生成する
	static std::unique_ptr<IComponent> CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
};

#endif		// TURRETFACTORY_DEFINED