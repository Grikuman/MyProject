/*
	ファイル名：Player.cpp
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

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_currentState{},
	m_playerUIManager{},
	m_playerEffectManager{},
	m_camera{},
	m_position{ PLAYER_INITIAL_POS },
	m_velocity{},
	m_angle{},
	m_chargeCnt{},
	m_invincible{ false },
	m_invincibleTime{ MAX_INVINCIBLE },
	m_stamina{ MAX_STAMINA },
	m_hp{ MAX_HP },
	m_direction{ DirectX::SimpleMath::Vector3::Forward }
{
	// 待機状態を作成する
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	// 走り状態を作成する
	m_playerRunning = std::make_unique<PlayerRunning>(this); 
	// 回避状態を作成する
	m_playerRolling = std::make_unique<PlayerRolling>(this); 
	// 通常攻撃を作成する
	m_playerAttackingNormal = std::make_unique<PlayerAttackingNormal>(this); 
	//カメラを作成する
	m_camera = std::make_unique<NRLib::TPS_Camera>();
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
	// 待機状態を初期化する
	m_playerIdling->Initialize();
	// 待機状態を初期化する
	m_playerRunning->Initialize(); 
	// 待機状態を初期化する
	m_playerRolling->Initialize(); 
	// 待機状態を初期化する
	m_playerAttackingNormal->Initialize();
	// UIを管理するクラスを初期化する
	m_playerUIManager->Initialize();
	// エフェクトを管理するクラスを初期化する
	m_playerEffectManager->Initialize();
	// 初期の状態を設定する(初期状態：待機)
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update()
{	
	using namespace DirectX::SimpleMath;
	
	// 速度を初期化する
	m_velocity = Vector3::Zero;
	// 重力を加算する
	m_velocity.y -= GRAVITY;
	// 無敵処理
	Invincible();
	// スタミナ回復処理
	ChargeStamina();
	// 現在の状態を更新する
	m_currentState->Update();
	// カメラを更新する
	m_camera->Update(m_position, Matrix::CreateFromQuaternion(m_angle));
	// UIを管理するクラスを更新する
	m_playerUIManager->Update();
	// エフェクトを管理するクラスを更新する
	m_playerEffectManager->Update();
	// ビューとプロジェクションを設定する
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render()
{
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
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
}

//---------------------------------------------------------
// 攻撃しているか取得する
//---------------------------------------------------------
bool Player::IsAttack()
{
	// 攻撃中
	if (m_currentState == m_playerAttackingNormal.get())
	{
		return true;
	}
	// 攻撃中ではない
	return false;
}

//---------------------------------------------------------
// 無敵処理
//---------------------------------------------------------
void Player::Invincible()
{
	// 無敵の場合
	if (m_invincible)
	{
		// 無敵時間を減少させる
		m_invincibleTime--;
		// 無敵時間が終わった際に処理する
		if (m_invincibleTime <= 0.f)
		{
			m_invincibleTime = MAX_INVINCIBLE; // リセット
			m_invincible = false;              // 無敵解除
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
