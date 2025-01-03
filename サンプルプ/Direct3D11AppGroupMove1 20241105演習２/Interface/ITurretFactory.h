#pragma once
#ifndef IFACTORY_METHOD_DEFINED
#define IFACTORY_METHOD_DEFINED
#include "Interface/IComponent.h"

// 砲塔ファクトリインタフェースを定義する
class ITurretFactory
{
public:
	// 砲塔を生成する
	virtual std::unique_ptr<IComponent> CreateTurret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔下部を生成する
	virtual std::unique_ptr<IComponent> CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔中部を生成する
	virtual std::unique_ptr<IComponent> CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔上部を生成する
	virtual std::unique_ptr<IComponent> CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔砲台を生成する
	virtual std::unique_ptr<IComponent> CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔砲身を生成する
	virtual std::unique_ptr<IComponent> CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔プレートを生成する
	virtual std::unique_ptr<IComponent> CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// 砲塔脚を生成する
	virtual std::unique_ptr<IComponent> CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
};

#endif		// FACTORY_METHOD_DEFINED
