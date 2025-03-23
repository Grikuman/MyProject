#include "Framework/pch.h"
#include "Node/Obstacle.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Node/NodeBase.h"

// 障害物モデルスケール
const float Obstacle::OBSTACLE_MODEL_SCALE = 0.4f;

// コンストラクタ
Obstacle::Obstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	NodeBase(parent, initialPosition, initialAngle, 0.0f),
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(0),
	m_partID(OBSTACLE),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_graphics{},
	m_model{},
	m_worldMatrix{},
	m_mass(0.0f),
	m_collision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}

// デストラクタ
Obstacle::~Obstacle()
{
}

// 初期化する
void Obstacle::Initialize()
{
	// 「砲塔下部」モデルをロードする
	m_model = Resources::GetInstance()->GetObstacleModel();
}

// 通知する
void Obstacle::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// 更新する
inline void Obstacle::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// 現在の回転角を更新する
	m_currentAngle = currentAngle * m_initialAngle;
}

// 衝突判定を準備する
void Obstacle::PrepareCollision(ICollisionVisitor* visitor)
{
	UNREFERENCED_PARAMETER(visitor);
}

// 衝突判定する
void Obstacle::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	UNREFERENCED_PARAMETER(visitor);
	UNREFERENCED_PARAMETER(bullet);
}

// 部品を追加する
void Obstacle::Attach(std::unique_ptr<IComponent> turretPart)
{
}

// 部品を削除する
void Obstacle::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// 描画する
inline void Obstacle::Render()
{
	using namespace DirectX::SimpleMath;

	// ワールド行列を生成する
	m_worldMatrix = Matrix::CreateScale(OBSTACLE_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 「砲塔下部」を描画する
	m_graphics->DrawModel(m_model, m_worldMatrix);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 後処理を行う
void Obstacle::Finalize()
{
}
