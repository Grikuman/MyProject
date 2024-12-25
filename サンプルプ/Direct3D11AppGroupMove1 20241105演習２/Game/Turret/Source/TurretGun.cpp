#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretGun.h"
#include "Framework/Resources.h"
#include "Observer/Messenger.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretFort.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// コンストラクタ
TurretGun::TurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_GUN),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationGunAngle{},
	m_bulletAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_worldMatrix{},
	m_turret{},
	m_shotBulletNumber{},
	m_shotTimer{},
	m_timer{},
	m_collision(false)
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// 衝突判定ビジタークラスのインスタンスを取得する
	m_collisionVisitor = CollisionVisitor::GetInstance();
	// 砲塔のインスタンスを取得する
	m_turret = dynamic_cast<Turret*>(parent->GetParent()->GetParent()->GetParent()->GetParent());
}

// デストラクタ
TurretGun::~TurretGun()
{
	Finalize();
}

// 初期化する
void TurretGun::Initialize()
{
	using namespace DirectX::SimpleMath;
	// 「砲身」モデルをロードする
	m_model = Resources::GetInstance()->GetTurretGunModel();
}

// 通知する
void TurretGun::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);
	// 「砲身」の回転させる
	if (keys == DirectX::Keyboard::Space)
	{
		// 発射タイマーが0.0より大きい場合は発射タイマーを減らす
		if (m_shotTimer > 0.0f)
			// タイマーを減らす
			m_shotTimer -= (float)m_timer.GetElapsedSeconds();
		else
		{
			m_rotationGunAngle *= Quaternion::CreateFromAxisAngle(
				Vector3::Forward,
				DirectX::XMConvertToRadians(10.0f)
			);
			// 「砲弾」を発射する
			for (auto& bullet : m_turret->GetBullets())
			{
				// 使用されていない砲弾は発射できる
				if (bullet->GetBulletState() == IBullet::UNUSED)
				{
					// 「砲弾」を発射する
					Shoot(bullet.get());
					// 発射砲弾数をインクリメントする
					m_shotBulletNumber++;
					break;
				}
			}
			// キー入力時の初期値を設定する
			if (Messenger::GetCommandExecution() == false)
				// 初期値を設定する
				m_shotTimer = SHOT_INTERVAL;
			else
				// コマンド実行時の初期値を設定する
				m_shotTimer = COMMAND_SHOT_INTERVAL;
		}
	}
}

// 更新する
void TurretGun::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// タイマーを更新する
	m_timer = timer;
	// 現在の位置を更新する
	m_currentPosition = currentPosition + m_initialPosition;
	// 現在の砲身回転角を更新する
	m_currentAngle = m_rotationGunAngle * currentAngle *m_initialAngle;
	// 砲弾回転角を計算する
	m_bulletAngle = currentAngle * m_initialAngle;
	
	// スケール行列を生成する
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		// 回転行列を生成する
		Matrix::CreateFromQuaternion(m_currentAngle) *
		// 移動行列を生成する
		Matrix::CreateTranslation(m_currentPosition);
}

// 衝突判定を準備する
void TurretGun::PrepareCollision(ICollisionVisitor* visitor)
{
	// 衝突ビジターの衝突判定を準備する
	visitor->PrepareCollision(this);
}

// 衝突判定する
void TurretGun::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// 衝突判定を行う
	visitor->DetectCollision(this, bullet);
}

// 描画する
void TurretGun::Render()
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
}

// 後処理を行う
void TurretGun::Finalize()
{
}

// 砲弾を発射する
void TurretGun::Shoot(IBullet* bullet)
{
	// 「砲弾」位置を設定する
	bullet->SetPosition(m_currentPosition);
	// 「砲弾」初期回転角を設定する
	bullet->SetBulletAngle(m_bulletAngle);
	// 「砲弾」を発射する
	bullet->SetBulletState(IBullet::FLYING);
}