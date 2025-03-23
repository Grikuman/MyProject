#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretMiddle.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretTop.h"
#include "Turret/Header/TurretPlate.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"
#include "Command/Header/MoveCommand.h"
#include "Command/Header/FloatCommand.h"
#include "Command/Header/RotateCommand.h"
#include "Command/Header/PlateCommand.h"
//#include "Command/Header/ShootCommand.h"
//#include "Command/Header/MoveGunUpCommand.h"
//#include "Command/Header/MoveGunDownCommand.h"


// コンストラクタ
TurretMiddle::TurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_MIDDLE),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_turretParts{},
	m_worldMatrix{},
	m_collision(false),
	m_commandExecution(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
TurretMiddle::~TurretMiddle()
{
	Finalize();
}

// 初期化する
void TurretMiddle::Initialize()
{
	using namespace DirectX::SimpleMath;
	// 「砲塔中部」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretMiddleModel();
	// 「砲塔上部」を追加する
	Attach(TurretFactory::CreateTurretTop(this, Vector3(0.0f, 3.8f, 0.0f), 0.0f));
	// 「砲塔プレート」×４を追加する
	for (int plateIndex = 0; plateIndex < 4; plateIndex++)
	{
		// 「砲塔プレート」を追加する
		Attach(TurretFactory::CreateTurretPlate(this, Vector3(0.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(90.0f * plateIndex)));
	}
	// コマンダーのインスタンスを作成する
	m_commander = std::make_unique<Commander>();
}

// 通知する
void TurretMiddle::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	if (keys == DirectX::Keyboard::V)
	{
		// 移動マクロコマンドをセットアップする
		SetupCommander();
		// 線形補間比率をリセットする
		m_commander->ResetLerp();
		// 移動マクロコマンドを開始する
		m_commandExecution = true;
	}
}

// 更新する
void TurretMiddle::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 現在の位置を更新する
	if (m_commandExecution == false)
	{
		// 現在の位置を更新する
		m_currentPosition = currentPosition + m_initialPosition;
		// 現在の回転角を更新する
		m_currentAngle = currentAngle * m_initialAngle;
	}
	// マクロコマンドを実行する
	if (m_commander->GetMacroCommandNumber() && m_commandExecution == true)
	{
		// マクロコマンドを実行する
		m_commandExecution = m_commander->ExecuteMacroCommand(m_currentPosition, m_currentAngle);
	}
	// ワールド行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	// 「砲塔上部」を更新する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
}

// 衝突判定を準備する
void TurretMiddle::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
	// 「砲塔中部」「砲塔プレート」のPrepareCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔中部」「砲塔プレート」のPrepareCollision関数を呼び出す
		turretPart->PrepareCollision(visitor);
	}
}

// 衝突判定する
void TurretMiddle::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
	// 「砲塔中部」「砲塔プレート」のDetectCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔中部」「砲塔プレート」のDetectCollision関数を呼び出す
		turretPart->DetectCollision(visitor, bullet);
	}
}

// 砲塔部品を追加する
void TurretMiddle::Attach(std::unique_ptr<IComponent> turretPart)
{
	// 部品を追加する
	m_turretParts.emplace_back(std::move(turretPart));
}

// 砲塔部品を削除する
void TurretMiddle::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// 描画する
void TurretMiddle::Render()
{
	// ノード番号から砲塔部品にカラーを設定する
	m_collisionVisitor->SetTurretPartColor(m_nodeNumber, m_model, m_collision);
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 「砲塔下部」を描画する
	m_graphics->DrawModel(m_model, m_worldMatrix);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
#ifdef _DEBUG
	// 境界ボックスを描画する
	// m_collisionVisitor->DrawBoundingBox(m_partNumber, m_worldMatrix);
#endif
	// 「砲塔上部」「プレート」を描画する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// 後処理を行う
void TurretMiddle::Finalize()
{
}

// 移動コマンド
void TurretMiddle::SetupCommander()
{
	using namespace DirectX::SimpleMath;

	// コマンドパラメータリスト
	CommandParameterList commandParameterList[] =
	{
		{std::make_unique<PlateCommand>(Parameter(0.0f, 0.0f))},
		{std::make_unique<FloatCommand>(Parameter(5.0f, 0.0f))},
		{std::make_unique<MoveCommand>(Parameter(20.0f, 0.0f))},

		//{std::make_unique<ShootCommand>(Parameter(0.0f, -0.6f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, 1.2f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, -1.2f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, 1.2f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, -0.6f))},

		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},

		{std::make_unique<RotateCommand>(Parameter(0.0f, 180.0f))},
		{std::make_unique<MoveCommand>(Parameter(20.0f, 0.0f))},
		{std::make_unique<RotateCommand>(Parameter(0.0f, 180.0f))},
		{std::make_unique<FloatCommand>(Parameter(-5.0f, 0.0f))},
		{std::make_unique<PlateCommand>(Parameter(0.0f, 0.0f))}
	};

	// コマンドをクリアする
	if (m_commander->GetMacroCommandNumber()) 
	{ 
		// マクロコマンドをクリアする
		m_commander->ClearCommand();
	}

	for (auto& commadParameter : commandParameterList)
	{
		// コマンドパラメータをマクロコマンドに追加する
		m_commander->AddCommand(std::move(commadParameter.command));
	}
}


