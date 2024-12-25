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

// 砲塔を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurret(	IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, 	const float& initialAngle)
{
	// 砲塔を宣言する
	std::unique_ptr<IComponent> turret;
	// Turretクラスのインスタンスを生成する
	turret.reset(new Turret(parent, initialPosition, initialAngle));
	// 部品番号をリセットする
	Turret::ResetPartsNumber();
	// 初期化する
	turret->Initialize();
	// [↑] キーと「砲塔」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::Up, turret.get());
	// [↓] キーと「砲塔」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::Down, turret.get());
	// [←] キーと「砲塔」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::Left, turret.get());
	// [→] キーと「砲塔」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::Right, turret.get());
	// [C] キーと「砲塔」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::C, turret.get());
	// Turretクラスのインスタンスを返す
	return std::move(turret);
}

// 砲塔下部を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔下部を宣言する
	std::unique_ptr<IComponent> turretBottom;
	// TurretBottomクラスのインスタンスを生成する
	turretBottom.reset(new TurretBottom(parent, initialPosition, initialAngle));
	// 初期化する
	 turretBottom->Initialize();
	// Turretクラスのインスタンスを返す
	return std::move(turretBottom);
}

// 砲塔中部を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔中部を宣言する
	std::unique_ptr<IComponent> turretMiddle;
	// TurretMiddleクラスのインスタンスを生成する
	turretMiddle.reset(new TurretMiddle(parent, initialPosition, initialAngle));
	// 初期化する
	turretMiddle->Initialize();
	// [V] キーと「砲塔」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::V, turretMiddle.get());
	// Turretクラスのインスタンスを返す
	return std::move(turretMiddle);
}

// 砲塔上部を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔上部を宣言する
	std::unique_ptr<IComponent> turretTop;
	// TurretTopクラスのインスタンスを生成する
	turretTop.reset(new TurretTop(parent, initialPosition, initialAngle));
	// 初期化する
	turretTop->Initialize();
	// [A] キーと「砲塔上部」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::A, turretTop.get());
	// [D] キーと「砲塔上部」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::D, turretTop.get());
	// Turretクラスのインスタンスを返す
	return std::move(turretTop);
}

// 砲塔砲台を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔砲台を宣言する
	std::unique_ptr<IComponent> turretFort;
	// TurretForteクラスのインスタンスを生成する
	turretFort.reset(new TurretFort(parent, initialPosition, initialAngle));
	// 初期化する
	turretFort->Initialize();
	// [W] キーと「砲塔主砲」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::W, turretFort.get());
	// [S] キーと「砲塔主砲」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::S, turretFort.get());
	// Turretクラスのインスタンスを返す
	return std::move(turretFort);
}

// 砲塔砲身を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔砲身を宣言する
	std::unique_ptr<IComponent> turretGun;
	// TurretGunクラスのインスタンスを生成する
	turretGun.reset(new TurretGun(parent, initialPosition, initialAngle));
	// 初期化する
	turretGun->Initialize();
	// [Space] キーと「砲身」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::Space, turretGun.get());
	// Turretクラスのインスタンスを返す
	return std::move(turretGun);
}

// 砲塔プレートを生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔プレートを宣言する
	std::unique_ptr<IComponent> turretPlate;
	// TurretPlateクラスのインスタンスを生成する
	turretPlate.reset(new TurretPlate(parent, initialPosition, initialAngle));
	// 初期化する
	turretPlate->Initialize();
	// [P] キーと「砲塔中部プレート」をアタッチする
	Messenger::Attach(DirectX::Keyboard::Keyboard::P, turretPlate.get());
	// Turretクラスのインスタンスを返す
	return std::move(turretPlate);
}

// 砲塔脚を生成する
std::unique_ptr<IComponent> TurretFactory::CreateTurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 砲塔脚を宣言する
	std::unique_ptr<IComponent> turretFoot;
	// TurretFootクラスのインスタンスを生成する
	turretFoot.reset(new TurretFoot(parent, initialPosition, initialAngle));
	// 初期化する
	turretFoot->Initialize();
	// Turretクラスのインスタンスを返す
	return std::move(turretFoot);
}
