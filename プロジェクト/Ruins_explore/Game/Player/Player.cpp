/*
	ファイル: Player.cpp
	クラス  : プレイヤークラス
*/
#include "pch.h"
#include "Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_playerUIManager{},
	m_playerEffectManager{},
	m_playerIdling{},
	m_playerAttack{},
	m_currentState{},
	m_model{},
	m_camera{},
	m_velocity{},
	m_playerAngle{},
	m_chargeCnt{},
	m_invincible{false},
	m_invincibleTime{}
{
	//プレイヤー座標の初期化
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
	// 体力を設定
	m_hp = MAX_HP;
	// スタミナを設定
	m_stamina = MAX_STAMINA;
	// 無敵時間を設定する
	m_invincibleTime = 120.f;
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
	//D3Dデバイスを取得
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// UI管理クラスを作成
	m_playerUIManager = std::make_unique<PlayerUIManager>(this);
	m_playerUIManager->Initialize();

	// エフェクト管理クラスを作成する
	m_playerEffectManager = std::make_unique<PlayerEffectManager>(this);
	m_playerEffectManager->Initialize();

	//カメラを作成
	m_camera = std::make_unique<NRLib::TPS_Camera>();

	m_model = Resources::GetInstance()->GetModel(L"Player");

	// ステートを作成
	// アイドリング状態
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	m_playerIdling->Initialize();
	// アタック状態
	m_playerAttack = std::make_unique<PlayerAttack>(this);
	m_playerAttack->Initialize();
	// ダッシュ状態
	m_playerDash = std::make_unique<PlayerDash>(this);
	m_playerDash->Initialize();

	// 初期ステートを設定
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	UNREFERENCED_PARAMETER(elapsedTime);

    // キーボードを取得する
	auto kb = InputDevice::GetInstance()->GetKeyboardState();

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

	// 速度を初期化
	m_velocity = Vector3::Zero;

	//現在のステートを更新する
	m_currentState->Update(elapsedTime);

	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));

	// 移動量を補正する
	m_velocity *= 0.05f;

	// 回転を加味して実際に移動する
	m_position += Vector3::Transform(m_velocity, matrix);

	// カメラを更新する
	m_camera->Update(m_position, matrix);

	// UI管理クラスを更新する
	m_playerUIManager->Update();

	// エフェクト管理クラスを更新する
	m_playerEffectManager->Update();

	// ビューとプロジェクションを設定する
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());

	if (kb->F)
	{
		ChangeState(m_playerAttack.get());
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render()
{
	// プレイヤーのステートを描画する
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
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
	m_playerIdling.reset();
	m_playerAttack.reset();
	m_playerDash.reset();
}

NRLib::TPS_Camera* Player::GetCamera()
{
	return m_camera.get();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	Vector3 center = m_position; // 当たり判定球の中心
	float radius = 0.5f;         // サイズに応じて調整
	return DirectX::BoundingSphere(center, radius);
}

bool Player::GetIsAttack()
{
	if (m_currentState == m_playerAttack.get())
	{
		return true;
	}
	return false;
}

void Player::ChangeState(IState* newState)
{
	m_currentState = newState;
}