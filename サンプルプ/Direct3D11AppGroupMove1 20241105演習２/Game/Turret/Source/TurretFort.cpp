#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretFort.h"
#include "Observer/Messenger.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretGun.h"
#include "Framework/Resources.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// float値の範囲を制限する
inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) 	return min;
	else if (value > max) return max;
	return value;
}

// クォータニオンの範囲を制限する
inline DirectX::SimpleMath::Quaternion Clamp(const DirectX::SimpleMath::Quaternion& quaternion, const float& minAngle, const float& maxAngle)
{
	using namespace DirectX::SimpleMath;

	// クォータニオンをオイラー角に変換する
	Vector3 euler = quaternion.ToEuler();
	// X軸の角度をクランプする
	euler.x = Clamp(euler.x, minAngle, maxAngle);
	// Y軸の角度をクランプする
	euler.y = Clamp(euler.y, minAngle, maxAngle);
	// Z軸の角度をクランプする
	euler.z = Clamp(euler.z, minAngle, maxAngle);
	// クランプされたX軸の角度で新しいクォータニオンを作成する
	Quaternion quaternionX = Quaternion::CreateFromAxisAngle(Vector3::Right,euler.x);
	// クランプされたY軸の角度で新しいクォータニオンを作成する
	Quaternion quaternionY = Quaternion::CreateFromAxisAngle(Vector3::Up,euler.y);
	// クランプされたZ軸の角度で新しいクォータニオンを作成する
	Quaternion quaternionZ = Quaternion::CreateFromAxisAngle(Vector3::Forward,euler.z);
	// 各軸のクォータニオンを合成する
	return quaternionX * quaternionY * quaternionZ;
}

// コンストラクタ
TurretFort::TurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_FORT),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationFortAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_turretParts{},
	m_worldMatrix{},
	m_collision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
TurretFort::~TurretFort()
{
	Finalize();
}

// 初期化する
void TurretFort::Initialize()
{
	using namespace DirectX::SimpleMath;

	// 「砲台」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretFortModel();
	// 「砲身」を追加する
	Attach(TurretFactory::CreateTurretGun(this, Vector3(0.0f, -0.1f, 0.0f), 0.0f));
}

// 通知する
void TurretFort::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	//if (Messenger::GetCommandExecution())
	//	return;
	switch (keys)
	{
	case DirectX::Keyboard::W:
		// 「砲台」の上回転角を計算する
		m_rotationFortAngle *= Quaternion::CreateFromAxisAngle(-Vector3::Right, DirectX::XMConvertToRadians(Turret::VERTICAL_ROTATION_ANGLE));
		break;
	case DirectX::Keyboard::S:
		// 「砲台」の下回転角を計算する
		m_rotationFortAngle *= Quaternion::CreateFromAxisAngle(Vector3::Right, DirectX::XMConvertToRadians(Turret::VERTICAL_ROTATION_ANGLE));
		break;
	}
	// 上下角のクォータニオンをクランプする
	m_rotationFortAngle = Clamp(m_rotationFortAngle, DirectX::XMConvertToRadians(-30.0f), DirectX::XMConvertToRadians(30.0f));
}

// 更新する
void TurretFort::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 砲台ｖ補正位置
	Vector3 position(0.0f, -0.1f, -0.95f);
	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// 現在の回転角を更新する
	m_currentAngle = m_rotationFortAngle * currentAngle * m_initialAngle;
	// 補正位置を計算する
	Vector3 AdjustedPosition = Vector3::Transform(position, currentAngle * m_initialAngle);

	// スケール行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		// 回転行列を生成する
		Matrix::CreateFromQuaternion(m_currentAngle) *
		// 移動行列を生成する
		Matrix::CreateTranslation(m_currentPosition) *
		// 位置を調整する
		Matrix::CreateTranslation(AdjustedPosition);

	// 「砲身」を更新する
	for (auto& turretPart : m_turretParts)
	{
		// 砲身を更新する
		turretPart->Update(timer, m_currentPosition+AdjustedPosition, m_currentAngle);
	}
}

// 衝突判定を準備する
void TurretFort::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
	// 「砲身」のPrepareCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲身」のPrepareCollision関数を呼び出す
		turretPart->PrepareCollision(visitor);
	}
}

// 衝突判定する
void TurretFort::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
	// 「砲身」のDetectCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲身」のDetectCollision関数を呼び出す
		turretPart->DetectCollision(visitor, bullet);
	}
}

// 砲塔部品を追加する
void TurretFort::Attach(std::unique_ptr<IComponent> turretPart)
{
	// 部品を追加する
	m_turretParts.emplace_back(std::move(turretPart));
}

// 砲塔部品を削除する
void TurretFort::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// 描画する
void TurretFort::Render()
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
	
	// 「砲身」を描画する
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// 後処理を行う
void TurretFort::Finalize()
{
}
