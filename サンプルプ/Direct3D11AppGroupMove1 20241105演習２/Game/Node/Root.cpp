#include "Framework/pch.h"
#include "Node/Root.h"
#include "Turret/Header/Turret.h"

// コンストラクタ
Root::Root(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	NodeBase(parent, initialPosition, initialAngle, 0.0f),
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCountAfterCountUp()),
	m_partNumber(Turret::ResetPartsNumber()),
	m_partID{},
	m_nodes{},
	IdentityMatrix{},
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass(0.0f),
	m_collision(false)
{
}

// デストラクタ
Root::~Root()
{
}

// 初期化する
void Root::Initialize()
{
}

// 通知する
void Root::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// 更新する
void Root::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;

	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// 現在の回転角を更新する
	m_currentAngle = currentAngle * m_initialAngle;
	// ノードを更新する
	NodeBase::Update(timer, m_currentPosition, m_currentAngle);
}

// 衝突判定を準備する
void Root::PrepareCollision(ICollisionVisitor* visitor)
{
	UNREFERENCED_PARAMETER(visitor);
}

// 衝突判定する
void Root::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	UNREFERENCED_PARAMETER(visitor);
	UNREFERENCED_PARAMETER(bullet);
}

// 砲塔部品を追加する
void Root::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ノードを追加する
	NodeBase::Attach(move(turretPart));
}

// 砲塔部品を削除する
void Root::Detach(std::unique_ptr<IComponent> turretPart)
{
	// 部品を削除する
	NodeBase::Detach(move(turretPart));
}

// 描画する
void Root::Render()
{
	// ノードを描画する
	NodeBase::Render();
}
// 後処理を行う
void Root::Finalize()
{
	// ノードをクリアする
	m_nodes.clear();
}

