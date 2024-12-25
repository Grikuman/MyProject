#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretPlate.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// コンストラクタ
TurretPlate::TurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_PLATE),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_worldMatrix{},
	m_currentState(CLOSE),
	m_lerpT{},
	m_startPosition(CLOSE_POSITION),
	m_endPosition(OPEN_POSITION),
	m_lerpPosition(CLOSE_POSITION),
	m_collision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
TurretPlate::~TurretPlate()
{
	Finalize();
}

// 初期化する
void TurretPlate::Initialize()
{
	using namespace DirectX::SimpleMath;
	// 「砲塔プレート」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretMiddlePlateModel();
}

// 線形補間を行う
DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// 通知する
void TurretPlate::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	// [P]キーで「プレート」を開閉する
	if (keys == DirectX::Keyboard::Keyboard::P)
	{
		// 移動状態に遷移する
		m_currentState = State::MOVE;
	}
}

// 更新する
void TurretPlate::Update(DX::StepTimer const& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// プレートを開閉する
	MovePlate();
	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// 現在の回転角を更新する
	m_currentAngle = currentAngle * m_initialAngle;
	// ワールド行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateTranslation(m_lerpPosition) *													// 砲塔プレート線形補間位置
		Matrix::CreateFromQuaternion(m_currentAngle) *										// 砲塔中部回転角＋初期回転角
		Matrix::CreateTranslation(m_currentPosition);												// 砲塔中部位置
}

// 衝突判定を準備する
void TurretPlate::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
}

// 衝突判定する
void TurretPlate::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
}

// プレートを開閉する
void TurretPlate::MovePlate()
{
	// プレートが移動状態の場合
	if (m_currentState == State::MOVE)
	{
		// 補間係数が1.0未満の場合
		if (m_lerpT < 1.0f)
		{
			// 線形補間位置を計算する
			m_lerpPosition = Lerp(m_startPosition, m_endPosition, m_lerpT);
			// 補間係数を増分する
			m_lerpT += 0.01f;
		}
		else
		{
			// 補間係数をクリアする
			m_lerpT = 0.0f;
			// 現在の終了位置がオープン位置と等しい場合
			if (m_endPosition == OPEN_POSITION)
			{
				// 現在の終了位置を開始位置に設定する
				m_startPosition = m_endPosition;
				// 終了位置にクローズ位置を設定する
				m_endPosition = CLOSE_POSITION;
				// 現在の状態をオープン状態に設定する
				m_currentState = State::OPEN;
			}
			// 現在の終了位置がクローズ位置と等しい場合
			else if (m_endPosition == CLOSE_POSITION)
			{
				// 現在の終了位置を開始位置に設定する
				m_startPosition = m_endPosition;
				// 終了位置にオープン位置を設定する
				m_endPosition = OPEN_POSITION;
				// 現在の状態をクローズ状態に設定する
				m_currentState = State::CLOSE;
			}
		}
	}
}

// 描画する
void TurretPlate::Render()
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
void TurretPlate::Finalize()
{
}
