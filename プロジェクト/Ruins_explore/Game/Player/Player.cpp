/*
	ayer.cpp
	　　　概要：プレイヤーの情報を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Resources.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

#include "Game/Player/Parts/PlayerBody.h"

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
	m_position{ PLAYER_INITIAL_POS },
	m_velocity{},
	m_angle{},
	m_chargeCnt{},
	m_invincible{ false },
	m_invincibleTime{ MAX_INVINCIBLE },
	m_stamina{ MAX_STAMINA },
	m_hp{ MAX_HP }
{
	//カメラを作成する
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	// パーツを作成する
	m_playerBody = std::make_unique<PlayerBody>(this);
	// プレイヤーのステートを作成する
	m_playerWalk    = std::make_unique<PlayerWalk>(this);
	m_playerAttack  = std::make_unique<PlayerAttack>(this);
	m_playerDash    = std::make_unique<PlayerDash>(this);
	// プレイヤーのUI管理クラスを作成する
	m_playerUIManager = std::make_unique<PlayerUIManager>(this);
	// プレイヤーのエフェクト管理クラスを作成する
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
	// ステートを初期化する
	m_playerWalk->Initialize();
	m_playerAttack->Initialize();
	m_playerDash->Initialize();
	// プレイヤーの体を初期化する
	m_playerBody->Initialize();
	// UIを管理するクラスを初期化する
	m_playerUIManager->Initialize();
	// エフェクトを管理するクラスを初期化する
	m_playerEffectManager->Initialize();
	// 初期の状態を設定する(初期状態：歩き)
	m_currentState = m_playerWalk.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	
	using namespace DirectX::SimpleMath;
	
	// 速度を初期化する
	m_velocity = Vector3::Zero;
	// 重力加算
	m_velocity.y -= GRAVITY * 0.5f;

	// 無敵処理
	Invincible();
	// スタミナ回復処理
	ChargeStamina();
	// 現在の状態を更新する
	m_currentState->Update(elapsedTime);
	// カメラを更新する
	m_camera->Update(m_position, Matrix::CreateFromQuaternion(m_angle));
	// UIを管理するクラスを更新する
	m_playerUIManager->Update();
	// エフェクトを管理するクラスを更新する
	m_playerEffectManager->Update();
	// プレイヤーの体を更新する
	m_playerBody->Update();

	// ビューとプロジェクションを設定する
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render()
{
	// プレイヤーの体を描画する
	m_playerBody->Render();
	// 現在の状態を描画をする
	m_currentState->Render();
	// UIを管理するクラスを描画する
	m_playerUIManager->Render();
	// エフェクトを管理するクラス描画する
	m_playerEffectManager->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Player::Finalize()
{
	m_playerBody->Finalize();
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
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

//---------------------------------------------------------
// バウンディングボックスを取得する
//---------------------------------------------------------
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
			m_invincibleTime = MAX_INVINCIBLE; // リセット
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
