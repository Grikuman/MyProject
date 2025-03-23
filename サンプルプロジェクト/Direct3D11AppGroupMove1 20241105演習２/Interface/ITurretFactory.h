#pragma once
#ifndef IFACTORY_METHOD_DEFINED
#define IFACTORY_METHOD_DEFINED
#include "Interface/IComponent.h"

// �C���t�@�N�g���C���^�t�F�[�X���`����
class ITurretFactory
{
public:
	// �C���𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C�������𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C�������𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C���㕔�𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C���C��𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C���C�g�𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C���v���[�g�𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
	// �C���r�𐶐�����
	virtual std::unique_ptr<IComponent> CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle) = 0;
};

#endif		// FACTORY_METHOD_DEFINED
