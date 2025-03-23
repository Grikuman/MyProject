#include "pch.h"
#include "Mario.h"
#include "PlayScene.h"
#include "DeviceResources.h"

class Standing;
class Downing;
class Jumping;
class Running;

// コンストラクタ
Mario::Mario(PlayScene* playScene)
:
m_playScene(playScene),																				// プレイシーン
m_standing{},																									// スタンディング
m_downing{},																									// ダウニイング
m_jumping{},																									// ジャンピング
m_position(DirectX::SimpleMath::Vector2(100.0f, PlayScene::GROUND)),	// 初期位置
m_velocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),									// 速度	
m_acceleration(DirectX::SimpleMath::Vector2(0.0f, 0.4f)),							// 加速度
m_currentState{},																							// 現在の状態
m_direction(Direction::RIGHT)																		// 向き
{
}

// デストラクタ
Mario::~Mario()
{
}

// 初期化する
void Mario::Initialize()
{
	// デバイスを取得する
	auto device = m_graphics->GetInstance()->GetDeviceResources()->GetD3DDevice();
	
	// 「立ち」テクスチャ
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\standing.png", nullptr, m_standingTexture.GetAddressOf());
	// 「屈む」テクスチャ
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\downing.png", nullptr, m_downingTexture.GetAddressOf());
	// 「ジャンプ」テクスチャ
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\jumping.png", nullptr, m_jumpingTexture.GetAddressOf());

	// 「立ち」状態を生成する
	m_standing = std::make_unique<Standing>(this);
	// 「屈む」状態を生成する
	m_downing = std::make_unique<Downing>(this);
	// 「ジャンプ」状態を生成する
	m_jumping = std::make_unique<Jumping>(this);

	// 初期状態を「立ち」に設定する
	m_currentState = m_standing.get();
}

// 更新する
void Mario::Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// 現在の状態を更新する
	m_currentState->Update(timer, keyboardStateTracker);
}

// 描画する
void Mario::Render()
{
	// 現在の状態を描画する
	m_currentState->Render();
}

// 後処理を行う
void Mario::Finalize()
{
}