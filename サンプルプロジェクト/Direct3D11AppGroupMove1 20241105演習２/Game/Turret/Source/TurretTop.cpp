#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Framework/Common.h"
#include "Turret/Header/TurretTop.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretFort.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// コンストラクタ
TurretTop::TurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_TOP),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationTopAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_turretPart{},
	m_turretParts{},
	m_worldMatrix{},
	m_collision(false),
	m_automaticTracking(true)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
TurretTop::~TurretTop()
{
	Finalize();
}

// 初期化する
void TurretTop::Initialize()
{
	using namespace DirectX::SimpleMath;
	// 「砲塔上部」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretTopModel();
	// 「砲台」を追加する
	Attach(TurretFactory::CreateTurretFort(this, Vector3(0.0f, 2.0f, 0.0f), 0.0f));
}

// 通知する
void TurretTop::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);
	
	switch (keys)
	{
	case DirectX::Keyboard::A:
		// 左回転を生成する
		m_rotationTopAngle = Quaternion::Concatenate(
			m_rotationTopAngle,
			Quaternion::CreateFromAxisAngle(
				Vector3::Up,
				DirectX::XMConvertToRadians(Turret::HORIZONTAL_ROTATION_ANGLE)
			)
		);
		break;
	case DirectX::Keyboard::D:
		// 右回転を生成する
		m_rotationTopAngle = Quaternion::Concatenate(
			m_rotationTopAngle,
			Quaternion::CreateFromAxisAngle(
				Vector3::Up,
				DirectX::XMConvertToRadians(-Turret::HORIZONTAL_ROTATION_ANGLE)
			)
		);
		break;
	}
}

// 更新する
void TurretTop::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 自動追尾がONの場合
	if (m_automaticTracking)
	{
		// ノード番号から所属するチーム番号を取得する
		int teamNumber = Team::GetTeamNumberForNodeNumber(m_nodeNumber);
		// 敵位置を取得する
		Vector3 enemyPosition = Team::GetEnemyTeamCenterPosition();
		// プレイヤー位置を取得する
		Vector3 playerPosition = Team::GetPlayerTeamCenterPosition();

		// 相手チームへのベクトルを計算する
		Vector3 toEnemyTeam = enemyPosition + playerPosition;
		// 相手チームを向くように回転する
		float angle = Team::GetOpponentSwitch() ?
			atan2(toEnemyTeam.x,toEnemyTeam.z) + DirectX::XM_PI :
			atan2(toEnemyTeam.x, toEnemyTeam.z);
		// 相手チームを向く回転クォータニオンを生成する
		Quaternion targetRotation = Quaternion::CreateFromYawPitchRoll(angle,0.f,0.f);
		// 現在の回転角を更新する
		m_currentAngle = targetRotation * currentAngle * m_initialAngle * m_rotationTopAngle;
	}
	else
	{
		// 現在の回転角を更新する
		m_currentAngle = currentAngle * m_initialAngle * m_rotationTopAngle;
	}

	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// ワールド行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	// 「砲台」を更新する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
}

// 衝突判定を準備する
void TurretTop::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
	// 「砲台」のPrepareCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲台」のPrepareCollision関数を呼び出す
		turretPart->PrepareCollision(visitor);
	}
}

// 衝突判定する
void TurretTop::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
	// 「砲台」のDetectCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲台」のDetectCollision関数を呼び出す
		turretPart->DetectCollision(visitor, bullet);
	}
}

// 砲塔部品を追加する
void TurretTop::Attach(std::unique_ptr<IComponent> turretPart)
{
	// 部品を追加する
	m_turretParts.emplace_back(std::move(turretPart));
}

// 砲塔部品を削除する
void TurretTop::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// 描画する
void TurretTop::Render()
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
	// 「砲台」を描画する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// 後処理を行う
void TurretTop::Finalize()
{
}
