#pragma once
#ifndef TURRETFACTORY_DEFINED
#define TURRETFACTORY_DEFINED
#include "Interface/IComponent.h"
#include "Interface/ITurretFactory.h"

// �C���t�@�N�g���N���X���`����
class TurretFactory : public ITurretFactory
{
public:
	// �C���𐶐�����
	static std::unique_ptr<IComponent> CreateTurret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C�������𐶐�����
	static std::unique_ptr<IComponent> CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C�������𐶐�����
	static std::unique_ptr<IComponent> CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C���㕔�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C���C��𐶐�����
	static std::unique_ptr<IComponent> CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C���C�g�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C���v���[�g�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �C���r�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
};

#endif		// TURRETFACTORY_DEFINED