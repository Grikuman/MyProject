#include "Framework/pch.h"
#include "Game/SoccerBall/SoccerBall.h"
#include "Framework/Resources.h"
#include "Game/PlayScene.h"
#include "Framework/DebugDraw.h"

// サッカーボールのホーム位置
const DirectX::SimpleMath::Vector3 SoccerBall::HOME_POSITION = DirectX::SimpleMath::Vector3(
	PlayScene::HOME_POSITION.x + 0.14f,
	PlayScene::HOME_POSITION.y + 0.001f,
	PlayScene::HOME_POSITION.z
);

// SI単位系を適用する
// 重力加速度 m/s^2
const float SoccerBall::GRAVITATION_ACCELERATION = -9.80665f;
// 質量 kg
const float SoccerBall::MASS = 0.450f;
// 半径 m
const float SoccerBall::RADIUS = 0.11f;
// 直径 m
const float SoccerBall::DIAMETER = 0.22f;
// 空気抵抗係数(Cd)
const float SoccerBall::DRAG_COEFFICIENT = 0.2f;
// 空気密度(ρ) kg/m^3
const float SoccerBall::AIR_DENSITY = 1.22f;
//サッカーボール直径断面積 m^2
const float SoccerBall::CROSS_SECTION = (0.25f * DirectX::XM_PI) * DIAMETER * DIAMETER;
// 空気抵抗係数(k)
// ボールに働く空気抵抗はボールの速度の二乗に比例する
const float SoccerBall::AIR_RESISTANCE = -0.5f * AIR_DENSITY * CROSS_SECTION * DRAG_COEFFICIENT;
// 摩擦係数
const float SoccerBall::FRICTION = -0.04f;
// 交差判定距離
const float SoccerBall::INTERSECT_JUDGEMENT_DISTANCE = 10.0f;

class PlayScene;

// コンストラクタ
SoccerBall::SoccerBall(PlayScene* playScene, const float& mass, const float& angle, const float& scale, const DirectX::SimpleMath::Vector3& position)
	:
	m_totalSeconds(0.0f),									// 総秒数
	m_playScene(playScene),							// プレイシーン
	m_graphics{},													// グラフィックス
	m_context{},														// デバイスコンテキスト
	m_deviceResources{},									// デバイスリソース
	m_soccerBallModel{},									// モデル
	m_quaternion{},												// 回転クォータニオン
	m_mass(mass),												// 質量
	m_angle(angle),												// 角度
	m_position(position),									// 位置
	m_velocity{},														// 速度
	m_acceralation{},											// 加速度
	m_radius(RADIUS),										// 半径
	m_scale(scale),												// スケール
	m_boundingSphere{}									// バウンディングスフィア
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// デバイスリソースを取得する
	m_deviceResources = m_graphics->GetDeviceResources();
	// デバイスを取得する
	m_device = m_deviceResources->GetD3DDevice();
}

// デストラクタ
SoccerBall::~SoccerBall()
{
}

// リセットする
void SoccerBall::Reset()
{
	// 初期位置を設定する
	m_position = SoccerBall::HOME_POSITION;
	// 速度を初期化する
	m_velocity = DirectX::SimpleMath::Vector3::Zero;
	// 加速度を設定する
	m_acceralation = DirectX::SimpleMath::Vector3(0.0f, GRAVITATION_ACCELERATION, 0.0f);
}

// 初期化する
void SoccerBall::Initialize()
{
	// サッカーボールモデルを取得する
	m_soccerBallModel = Resources::GetInstance()->GetSoccerBallModel();
	// 総秒数を初期化する
	m_totalSeconds = 0.0f;
	// 境界球を生成する(追加:20240513)
	m_boundingSphere = DirectX::BoundingSphere();
	// 境界球の半径を設定する
	m_boundingSphere.Radius = SoccerBall::RADIUS * 0.4f;
}

// 更新する
void SoccerBall::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);

	// 重力加速度が設定されていない場合は更新しない
	if (m_acceralation.y == 0.0f)
		return;

	// 速度を計算する
	m_velocity += m_acceralation * elapsedTime;
	// 向きを設定する
	Vector3 heading = m_velocity;
	// 空気抵抗により減速する
	m_velocity += heading * AIR_RESISTANCE;
	// 位置を計算する
	m_position += m_velocity * elapsedTime;

	// サッカーボールの回転軸を設定する
	Vector3 axis = Vector3(heading.y, 0.0f, -heading.x);
	// サッカーボールが移動している場合
	if (m_velocity.Length())
	{
		// 回転角を計算する
		float angle = (m_velocity.Length() / m_radius) * 0.006f;
		// クォータニオンを生成する
		m_quaternion *= Quaternion::CreateFromAxisAngle(axis, angle);
	}

	// ボールを弾ませる
	if (m_position.y <= 0.0f)
	{
		// 位置を補正する
		m_position = Vector3(m_position.x, 0.0f, m_position.z);
		// 速度を反転させる
		m_velocity.y = -m_velocity.y;
		// 減速率(85%)を適用する
		m_velocity = m_velocity * 0.85f;
	}
	if (m_velocity.Length() < 0.1f)
	{
		// 初期位置を設定する
		m_position = SoccerBall::HOME_POSITION;
		// 加速度を初期化する
		m_acceralation = Vector3::Zero;
		// 速度を初期化する
		m_velocity = Vector3::Zero;
	}
	// 境界球の中心点に位置を設定する
	m_boundingSphere.Center = m_position;

}

// 描画する
void SoccerBall::Render()
{
	using namespace DirectX::SimpleMath;

	// ワールド行列を計算する
	Matrix worldMatrix = Matrix::CreateScale(m_scale) *
		Matrix::CreateFromQuaternion(m_quaternion) *
		Matrix::CreateTranslation(GetPosition().x, GetPosition().y + m_radius * 0.23f, GetPosition().z);

	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// サッカーボールを描画する
	m_graphics->DrawModel(m_soccerBallModel, worldMatrix);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
	// 境界球を描画する
	//DrawBoundingSphere();
}

// 境界球を描画する
void SoccerBall::DrawBoundingSphere()
{
	using namespace DirectX::SimpleMath;

	DirectX::BoundingSphere worldBoundingSphere;
	// 境界球にワールド行列でトランスフォームする
	m_boundingSphere.Transform(worldBoundingSphere, m_worldMatrix);
	// 境界球の中心点を設定する
	worldBoundingSphere.Center = m_position;
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 砲塔の境界球を描画する
	DX::Draw(m_graphics->GetPrimitiveBatch(), worldBoundingSphere, DirectX::Colors::Yellow);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 後処理を行う
void SoccerBall::Finalize()
{
}

// サッカーボールを蹴る(追加:20240513)
void  SoccerBall::Shoot(const DirectX::SimpleMath::Vector3& direction, const float& impulsiveForce)
{
	using namespace DirectX::SimpleMath;

	// 蹴る角度を設定する
	Vector3 shootDirection = direction;
	// 正規化する
	shootDirection.Normalize();
	// F = MVを適用する(力積を考慮)
	m_velocity = shootDirection * impulsiveForce * 0.01f / m_mass;
}


