#include "Framework/pch.h"
#include "Game/Factory/TurretFactory.h"
#include "Game/Team/Team.h"
#include "Game/Turret/Header/Turret.h"
#include "Game/Turret/Header/TurretBottom.h"
#include "Game/Turret/Header/TurretMiddle.h"
#include "Game/Turret/Header/TurretTop.h"
#include "Game/Turret/Header/TurretFort.h"
#include "Game/Turret/Header/TurretGun.h"
#include "Game/Turret/Header/TurretPlate.h"
#include "Game/Turret/Header/TurretFoot.h"
#include "Observer/Messenger.h"

// �C���𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurret(	IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, 	const float& initialAngle)
{
	// �C����錾����
	std::unique_ptr<IComponent> turret;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	turret.reset(new Turret(parent, initialPosition, initialAngle));
	// ���i�ԍ������Z�b�g����
	Turret::ResetPartsNumber();
	// ����������
	turret->Initialize();
	// [��] �L�[�Ɓu�C���v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::Up, turret.get());
	// [��] �L�[�Ɓu�C���v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::Down, turret.get());
	// [��] �L�[�Ɓu�C���v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::Left, turret.get());
	// [��] �L�[�Ɓu�C���v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::Right, turret.get());
	// [C] �L�[�Ɓu�C���v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::C, turret.get());
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turret);
}

// �C�������𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C��������錾����
	std::unique_ptr<IComponent> turretBottom;
	// TurretBottom�N���X�̃C���X�^���X�𐶐�����
	turretBottom.reset(new TurretBottom(parent, initialPosition, initialAngle));
	// ����������
	 turretBottom->Initialize();
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretBottom);
}

// �C�������𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C��������錾����
	std::unique_ptr<IComponent> turretMiddle;
	// TurretMiddle�N���X�̃C���X�^���X�𐶐�����
	turretMiddle.reset(new TurretMiddle(parent, initialPosition, initialAngle));
	// ����������
	turretMiddle->Initialize();
	// [V] �L�[�Ɓu�C���v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::V, turretMiddle.get());
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretMiddle);
}

// �C���㕔�𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C���㕔��錾����
	std::unique_ptr<IComponent> turretTop;
	// TurretTop�N���X�̃C���X�^���X�𐶐�����
	turretTop.reset(new TurretTop(parent, initialPosition, initialAngle));
	// ����������
	turretTop->Initialize();
	// [A] �L�[�Ɓu�C���㕔�v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::A, turretTop.get());
	// [D] �L�[�Ɓu�C���㕔�v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::D, turretTop.get());
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretTop);
}

// �C���C��𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C���C���錾����
	std::unique_ptr<IComponent> turretFort;
	// TurretForte�N���X�̃C���X�^���X�𐶐�����
	turretFort.reset(new TurretFort(parent, initialPosition, initialAngle));
	// ����������
	turretFort->Initialize();
	// [W] �L�[�Ɓu�C����C�v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::W, turretFort.get());
	// [S] �L�[�Ɓu�C����C�v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::S, turretFort.get());
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretFort);
}

// �C���C�g�𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C���C�g��錾����
	std::unique_ptr<IComponent> turretGun;
	// TurretGun�N���X�̃C���X�^���X�𐶐�����
	turretGun.reset(new TurretGun(parent, initialPosition, initialAngle));
	// ����������
	turretGun->Initialize();
	// [Space] �L�[�Ɓu�C�g�v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::Space, turretGun.get());
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretGun);
}

// �C���v���[�g�𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C���v���[�g��錾����
	std::unique_ptr<IComponent> turretPlate;
	// TurretPlate�N���X�̃C���X�^���X�𐶐�����
	turretPlate.reset(new TurretPlate(parent, initialPosition, initialAngle));
	// ����������
	turretPlate->Initialize();
	// [P] �L�[�Ɓu�C�������v���[�g�v���A�^�b�`����
	Messenger::Attach(DirectX::Keyboard::Keyboard::P, turretPlate.get());
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretPlate);
}

// �C���r�𐶐�����
std::unique_ptr<IComponent> TurretFactory::CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// �C���r��錾����
	std::unique_ptr<IComponent> turretFoot;
	// TurretFoot�N���X�̃C���X�^���X�𐶐�����
	turretFoot.reset(new TurretFoot(parent, initialPosition, initialAngle));
	// ����������
	turretFoot->Initialize();
	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretFoot);
}
