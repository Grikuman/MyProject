#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretFoot.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// コンストラクタ
TurretFoot::TurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_FOOT),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_worldMatrix{},
	m_collision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
TurretFoot::~TurretFoot()
{
	Finalize();
}

// 初期化する
void TurretFoot::Initialize()
{
	using namespace DirectX::SimpleMath;
	// 「砲塔脚」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretBottomFootModel();
}

// 通知する
void TurretFoot::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// 更新する
void TurretFoot::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// 現在の回転角を更新する
	m_currentAngle = currentAngle * m_initialAngle;
	// ワールド行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
}

// 衝突判定を準備する
void TurretFoot::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
}

// 衝突判定する
void TurretFoot::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
}

// 描画する
void TurretFoot::Render()
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
	//m_collisionVisitor->DrawBoundingBox(m_partNumber, m_worldMatrix);
#endif
}

// 後処理を行う
void TurretFoot::Finalize()
{
}
