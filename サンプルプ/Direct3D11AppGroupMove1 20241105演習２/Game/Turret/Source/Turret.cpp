#include "Framework/pch.h"
#include "Turret/Header/Turret.h"
#include "Utilities/DebugDraw.h"
#include "Observer/Messenger.h"
#include "Team/Team.h"
#include "Factory/TurretFactory.h"
#include "Bullet/BulletFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Steering/SteeringBehavior.h"
#include "Steering/SteeringBehaviorParameter.h"
#include "PlayScene.h"
#include "Turret/Header/TurretBottom.h"

// 最大砲弾数
const int Turret::MAX_BULLET_NUMBER = 300;
// 砲塔スピード
const DirectX::SimpleMath::Vector3 Turret::SPEED(0.0f, 0.0f, 0.6f);
// 砲塔部品左右回転角
const float Turret::HORIZONTAL_ROTATION_ANGLE = 0.1f;
// 砲台上下回転角
const float Turret::VERTICAL_ROTATION_ANGLE = 0.1f;
// モデルスケール
const DirectX::SimpleMath::Vector3 Turret::TURRET_MODEL_SCALE(0.0004f);
// 砲塔境界ボックススケール
const DirectX::SimpleMath::Vector3 Turret::TURRET_BOUNDINGBOX_SCALE(0.0004);

// 部品カウンター
int Turret::s_partsNumber = 0;

// コンストラクタ
Turret::Turret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCountAfterCountUp()),
	m_partNumber(Turret::GetPartsNumber()),
	m_partID(Turret::TURRET),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationTurretAngle{},
	m_velocity{},
	m_acceleration{},
	m_heading{},
	m_maxSpeed(SteeringBehaviorParameter::MAX_SPEED),
	m_maxTurnRate(SteeringBehaviorParameter::MAX_TURN_RATE),
	m_maxForce(SteeringBehaviorParameter::MAX_FORCE),
	m_mass(100.0f),
	m_graphics{},
	m_collisionVisitor{},
	m_turretParts{},
	m_worldMatrix{},
	m_turretBoundingSphere{},
	m_turretCenter{},
	m_collision(false),
	m_move(false),
	m_neighbors{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// デストラクタ
Turret::~Turret()
{
	Finalize();
}

// 初期化する
void Turret::Initialize()
{
	using namespace DirectX::SimpleMath;

	// 「砲塔下部」を生成する
	Attach(TurretFactory::CreateTurretBottom(this, Vector3(0.0f, 3.8f, 0.0f), 0.0f));
	// 「砲弾工場」に砲弾生成を依頼する
	m_bullets = BulletFactory::CreateBullets(MAX_BULLET_NUMBER, m_nodeNumber, IBullet::UNUSED);
	// 境界球を生成する
	m_turretBoundingSphere = CreateBoundingSphere(9.0f);
	// 衝突判定の準備を開始する
	m_collisionVisitor->StartPrepareCollision(this);
	// 操舵行動を生成する
	m_steeringBehavior = std::make_unique<SteeringBehavior>(this);
}

// 通知する
void Turret::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	// コマンド実行中は砲塔の移動と回転は実行できない
	if (Messenger::GetCommandExecution())
		return;

	switch (keys)
	{
	case DirectX::Keyboard::Up:
		// 砲塔移動中は復帰する
		if (IsMove()) 
			break;
		// 前方への移動速度を計算する
		m_velocity += Vector3::Transform(Turret::SPEED, m_currentAngle);
		break;
	case DirectX::Keyboard::Down:
		// 砲塔移動中は復帰する
		if (IsMove()) 
			break;
		// 後方への移動速度を計算する
		m_velocity -= Vector3::Transform(Turret::SPEED, m_currentAngle);
		break;
	case DirectX::Keyboard::Left:
		// 砲塔移動中は復帰する
		 if (IsMove()) 
			break;
		// 左回転を生成する
		m_rotationTurretAngle *= Quaternion::CreateFromAxisAngle(
			Vector3::Up,
			DirectX::XMConvertToRadians(Turret::HORIZONTAL_ROTATION_ANGLE)
		);
		break;
	case DirectX::Keyboard::Right:
		// 砲塔移動中は復帰する
		 if (IsMove()) 
			break;
		// 右回転を生成する
		m_rotationTurretAngle *= Quaternion::CreateFromAxisAngle(
			Vector3::Up,
			DirectX::XMConvertToRadians(-Turret::HORIZONTAL_ROTATION_ANGLE)
		);
		break;
	case DirectX::Keyboard::C:
		// 砲塔砲弾をチャージする
		ChargeBullets();
		break;
	}
}

// 通知する(マウス)
void Turret::OnLeftButtonClicked(const DirectX::SimpleMath::Vector3& position)
{
	UNREFERENCED_PARAMETER(position);

	// 到着行動を有効にする
	ArriveOn(position);
	// 分離行動を有効にする
	SeparationOn();
	// 整列行動を有効にする
	//AlignmentOn();
	// 障害物回避行動を有効にする
	ObstacleAvoidanceOn(position);
	// 移動を開始する
	Move(true);
}

// 更新する
void Turret::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 経過時間を取得する
	float elapsedTime = float(timer.GetElapsedSeconds());
	// 砲塔が移動している場合の処理を行う
	if (m_move) 
	{
		// 操舵力を計算する
		Vector3 steeringForce = m_steeringBehavior->Calculate();
		// 操舵力(加速度 = 操舵力 / 質量)から加速度を計算する
		Vector3 acceleration = steeringForce / m_mass;
		// 速度に加速度を加算する
		m_velocity +=  acceleration * elapsedTime;
		// 現在の位置を更新する
		m_currentPosition += m_velocity * elapsedTime;
		// 速度から回転角を計算する
		m_currentAngle = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, atan2f(m_velocity.x, m_velocity.z));
		// 砲塔が停止している場合
		if (m_velocity.Length() < 0.1f)
		{
			// 速度をリセットする
			m_velocity = Vector3::Zero;
			// 現在の位置を初期位置に設定する
			m_initialPosition = m_currentPosition;
			// 移動を完了する
			Move(false);
		}
	}
	else
	{
		// 現在の位置を更新する
		m_currentPosition = currentPosition + m_initialPosition + m_velocity;
		// 現在の回転角を更新する
		m_currentAngle = currentAngle * m_initialAngle * m_rotationTurretAngle;
	}
	// 砲塔の境界球の中心点を設定する
	m_turretCenter = m_currentPosition + DirectX::SimpleMath::Vector3(0.0f, 8.0f, 0.0f);
	// 境界球の中心点を設定する
	m_turretBoundingSphere.Center = m_turretCenter;
	// 砲塔部品を更新する
	for (auto& turretPart : m_turretParts)
	{
		// 砲塔部品を更新する
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
	// 飛弾中の砲弾を更新する
	for (auto& bullet : m_bullets)
	{
		// 砲弾が飛弾している場合 砲弾を更新する
		if (bullet->GetBulletState() == IBullet::FLYING)
		{
			// 砲弾を更新する
			bullet->Update(timer);
		}
	}
}

// 砲塔境界球を作成する
DirectX::BoundingSphere Turret::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// 境界球の半径を設定する
	turretBoundingSphere.Radius = radius;
	// 境界球を返す
	return turretBoundingSphere;
}

// 衝突判定を準備する
void Turret::PrepareCollision(ICollisionVisitor* visitor)
{
	// 「砲塔下部」のPrepareCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔下部」のPrepareCollision関数を呼び出す
		turretPart->PrepareCollision(visitor);
	}
}

// 衝突判定する
void Turret::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
	// 「砲塔下部」のDetectCollision関数を呼び出す
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔下部」のDetectCollision関数を呼び出す
		turretPart->DetectCollision(visitor, bullet);
	}
}

// 自砲塔とプレイヤー砲塔から発射された砲弾の衝突判定を行う(関数名の変更)
void Turret::DetectCollisionTurret()
{
	// 自砲塔が所属するチーム番号を取得する
	int team = Team::GetTeamNumberForNodeNumber(m_nodeNumber);
	// 自チームがプレイヤーチームの場合衝突判定を除外するために復帰する
	if (team == Team::GetPlayerTeamNumber())
		return;
	// プレイヤーチーム番号を取得する
	int playerTeamNumber = Team::GetOpposingTeamNumber(team);
	// プレイヤーチームのノード番号配列を取得する
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);
	// プレイヤーノード配列からプレイヤーノード番号を取得する
	for (auto& playerNodeNumber : playerNodeNumbers)
	{
		// 砲塔参照リストからプレイヤー砲塔を取得する
		Turret* playerTurret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(playerNodeNumber));
		// プレイヤー砲塔の砲弾配列を取得する
		for (auto& bullet : playerTurret->GetBullets())
		{
			// プレイヤー砲塔から発射された「砲弾が飛弾中」で「自砲塔に砲弾」が衝突している場合 自砲塔の境界球(赤)を描画する
			if (bullet->GetBulletState() == IBullet::FLYING && m_turretBoundingSphere.Contains(*bullet->GetWorldBoundingBox()))
			{
				// 自砲塔の境界球(赤)を描画する
				DrawTurretBoundingSphere(true);
				// 「砲塔部品」と「砲弾」の衝突判定を行う
				DetectCollision(m_collisionVisitor, bullet.get());
			}
		}
	}
}

// 砲塔部品を追加する
void Turret::Attach(std::unique_ptr<IComponent> turretPart)
{ 
	// 砲塔部品を追加する
	m_turretParts.emplace_back(std::move(turretPart));
}

// 砲塔部品を削除する
void Turret::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// 描画する
void Turret::Render()
{
	// 砲塔部品を描画する
	for (auto& turretPart : m_turretParts)
	{
		// 「砲塔部品」を描画する
		turretPart->Render();
	}
	// 「砲塔境界球」を描画する
	// DrawTurretBoundingSphere(false);
	// 「砲塔」と「砲弾」の衝突判定を行う
	DetectCollisionTurret();
	// 飛弾中の「砲弾」を描画する
	for (auto& bullet : m_bullets)
	{
		// 飛弾中の「砲弾」を描画する
		if (bullet->GetBulletState() == IBullet::FLYING)
		{
			// 「砲弾」を描画する
			bullet->Render();
		}
	}
}

// 砲塔境界球を描画する
void Turret::DrawTurretBoundingSphere(bool collision)
{
	// 既定色を設定する
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;
	if (collision)
	{
		// 衝突時の境界球の色を設定する
		color = DirectX::Colors::Red;
	}
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
#ifdef _DEBUG
	// 「砲塔」の境界球を描画する
	// DX::Draw(m_graphics->GetPrimitiveBatch(), m_turretBoundingSphere, color);
#endif
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 後処理を行う
void Turret::Finalize()
{
	// 削除する部品をリセットする
}

// 砲弾をチャージする
void Turret::ChargeBullets()
{
	// 砲弾配列の砲弾を未使用にする
	for (auto& bullet : m_bullets)
	{
		// 砲弾を未使用にする
		bullet->SetBulletState(IBullet::UNUSED);
	}
}

// 近接砲塔配列を生成する(プレイシーンから呼び出される)
void Turret::CreateNeighbors(std::vector<int>& teamList)
{
	// 近接砲塔配列をクリアする
	m_neighbors.clear();
	for (auto& nodeNumber : teamList)
	{
		// 自砲塔でない場合 近接砲塔配列に砲塔を追加する
		if (nodeNumber != m_nodeNumber)
		{
			// 近接砲塔配列に砲塔を追加する
			m_neighbors.emplace_back(dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber)));
		}
	}
}


