[
	ayer.cpp
	　　　概要：プレイヤーの情報を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_playerUIManager{},
	m_playerEffectManager{},
	m_playerWalk{},
	m_playerAttack{},
	m_currentState{},
	m_camera{},
	m_position{ DirectX::SimpleMath::Vector3(0.0f, 5.0f, 0.0f) },
	m_velocity{},
	m_angle{},
	m_chargeCnt{},
	m_invincible{ false },
	m_invincibleTime{ 120.0f },
	m_stamina{ MAX_STAMINA },
	m_hp{ MAX_HP }
{
	//カメラを作成する
	m_camera = std::make_unique<NRLib::TPS_Camera>();

	// パーツを作成する
	m_parts.push_back(std::make_unique<PlayerBody>(this));
	m_parts.push_back(std::make_unique<PlayerRightHand>(this));
	m_parts.push_back(std::make_unique<PlayerLeftHand>(this));

	// プレイヤーのステートを作成
	m_playerWalk    = std::make_unique<PlayerWalk>(this);
	m_playerAttack  = std::make_unique<PlayerAttack>(this);
	m_playerDash    = std::make_unique<PlayerDash>(this);
	m_playerJump    = std::make_unique<PlayerJump>(this);

	// UI管理クラスを作成
	m_playerUIManager = std::make_unique<PlayerUIManager>(this);
	// エフェクト管理クラスを作成する
	m_playerEffectManager = std::make_unique<PlayerEffectManager>(this);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Player::~Player()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Player::Initialize()
{
	// パーツを初期化する
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	// ステートを初期化する
	m_playerWalk->Initialize();
	m_playerAttack->Initialize();
	m_playerDash->Initialize();
	m_playerJump->Initialize();
	// UI管理クラスを初期化する
	m_playerUIManager->Initialize();
	// エフェクト初期化する
	m_playerEffectManager->Initialize();

	// 初期ステートを設定
	m_currentState = m_playerWalk.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);
	// 速度を初期化
	m_velocity = Vector3::Zero;

	m_velocity.y -= GRAVITY * 0.5f;

	// 無敵処理
	Invincible();
	// スタミナ回復処理
	ChargeStamina();

	//現在のステートを更新する
	m_currentState->Update(elapsedTime);

	//m_velocity.y -= GRAVITY;

	// Y軸を中心にカメラも回転させる
	m_camera->Update(m_position, Matrix::CreateFromQuaternion(m_angle)); 

	// UI管理クラスを更新する
	m_playerUIManager->Update();
	// エフェクト管理クラスを更新する
	m_playerEffectManager->Update();
	// パーツを更新する
	for(auto& parts : m_parts)
	{
		parts->Update();
	}

	// ビューとプロジェクションを設定する
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render()
{
	// パーツを描画する
	for(auto& parts : m_parts)
	{
		parts->Render();
	}

	// 現在のステートを描画をする
	m_currentState->Render();

	// UI管理クラスを描画する
	m_playerUIManager->Render();

	// エフェクト管理クラス描画する
	m_playerEffectManager->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Player::Finalize()
{
	for(auto& parts : m_parts)
	{
		parts->Finalize();
	}
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
	m_playerWalk.reset();
	m_playerAttack.reset();
	m_playerDash.reset();
}


//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
DirectX::BoundingSphere Player::GetBoundingSphere()
{
	DirectX::SimpleMath::Vector3 center = m_position; // 当たり判定球の中心
	float radius = 0.5f;         // サイズに応じて調整
	return DirectX::BoundingSphere(center, radius);

}

DirectX::BoundingBox Player::GetBoundingBox()
{
	// 当たり判定ボックスの中心を設定
	DirectX::SimpleMath::Vector3 center = m_position;

	// ボックスの大きさ（半径）を設定
	DirectX::SimpleMath::Vector3 extents(1.0f, 1.0f, 1.0f); // サイズに応じて調整

	return DirectX::BoundingBox(center, extents);
}

//---------------------------------------------------------
// プレイヤーの向きを取得する
//---------------------------------------------------------
DirectX::SimpleMath::Vector3 Player::GetForwardDirection()
{
	// 回転角度から方向ベクトルを計算
	//return DirectX::SimpleMath::Vector3(
	//	std::cos(DirectX::XMConvertToRadians(m_playerAngle)), // X
	//	0.0f,                    // Y（2D計算だから0で大丈夫）
	//	std::sin(DirectX::XMConvertToRadians(m_playerAngle))  // Z
	//);
	return DirectX::SimpleMath::Vector3(0,0,0);
}

//---------------------------------------------------------
// 攻撃しているか取得する
//---------------------------------------------------------
bool Player::IsAttack()
{
	if (m_currentState == m_playerAttack.get())
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------
// ステートを変更する
//---------------------------------------------------------
void Player::ChangeState(IPlayerState* newState)
{
	m_currentState = newState;
}
//---------------------------------------------------------
// 無敵処理
//---------------------------------------------------------
void Player::Invincible()
{
	// 無敵の場合は
	if (m_invincible)
	{
		// 無敵時間を減少させる
		m_invincibleTime--;
		// 無敵時間が終わると
		if (m_invincibleTime <= 0.f)
		{
			m_invincibleTime = 120.f; // リセット
			m_invincible = false;     // 無敵解除
		}
	}
}

//---------------------------------------------------------
// スタミナ回復処理
//---------------------------------------------------------
void Player::ChargeStamina()
{
	// スタミナ回復カウントを行う
	if (m_stamina != MAX_STAMINA)
	{
		m_chargeCnt++;
	}
	else // 最大の場合カウントをしない
	{
		m_chargeCnt = 0.f; // カウントリセット
	}
	// 3秒カウント
	if (m_chargeCnt >= 180.f)
	{
		m_stamina++;       // スタミナを回復する
		m_chargeCnt = 0.f; // カウントリセット
	}
}
