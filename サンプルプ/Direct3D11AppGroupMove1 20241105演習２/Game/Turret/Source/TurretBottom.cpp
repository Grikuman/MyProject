#include "Framework/pch.h"
#include "Turret/Header/TurretBottom.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Node/NodeBase.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretMiddle.h"
#include "Turret/Header/TurretFoot.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"


// コンストラクタ
TurretBottom::TurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_BOTTOM),
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
	m_rustTexture{},
	m_collision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
TurretBottom::~TurretBottom()
{
	Finalize();
}

// 初期化する
void TurretBottom::Initialize()                
{
	using namespace DirectX::SimpleMath;

	// 「砲塔下部」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretBottomModel();
	// 「砲塔中部」を追加する
	Attach(TurretFactory::CreateTurretMiddle(this, Vector3(0.0f, 8.3f, 0.0f), 0.0f));
	// 「砲塔脚」×４を追加する
	for (int footIndex = 0; footIndex < 4; footIndex++)
	{
		// 「砲塔脚」を追加する
		Attach(TurretFactory::CreateTurretFoot(this, Vector3(0.0f, 3.0f, 0.0f), DirectX::XMConvertToRadians(90.0f * footIndex)));
	}
}

// 通知する
void TurretBottom::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// 更新する
void TurretBottom::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 現在の位置を更新する
	m_currentPosition = currentPosition;
	// 現在の回転角を更新する
	m_currentAngle = currentAngle * m_initialAngle;
	// ワールド行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition + m_initialPosition);
	// 「砲塔中部」を更新する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
}

// 衝突判定を準備する
void TurretBottom::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
	// 「砲塔中部」「砲塔脚」のPrepareCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔中部」「砲塔脚」のPrepareCollision関数を呼び出す
		turretPart->PrepareCollision(visitor);
	}
}

// 衝突判定する
void TurretBottom::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
	// 「砲塔中部」「砲塔脚」のDetectCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔中部」「砲塔脚」のDetectCollision関数を呼び出す
		turretPart->DetectCollision(visitor, bullet);
	}
}

// 砲塔部品を追加する
void TurretBottom::Attach(std::unique_ptr<IComponent> turretPart)
{
	// 部品を追加する
	m_turretParts.emplace_back(std::move(turretPart));
}

// 砲塔部品を削除する
void TurretBottom::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// 描画する
void TurretBottom::Render()
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
	// 「砲塔中部」「砲塔脚」を描画する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// 後処理を行う
void TurretBottom::Finalize()
{
}
