#include "pch.h"
#include "Mario.h"
#include "DeviceResources.h"

// コンストラクタ
Mario::Mario(float x, float y)
	:
	m_currentState(State::STANDING_STATE),
	m_currentTexture(nullptr),
	m_standing(nullptr),
	m_jumping(nullptr),
	m_downing(nullptr),
	m_x(x),
	m_y(y),
	m_vx(0.0f),
	m_vy(0.0f),
	m_ax(0.0f),
	m_ay(0.2f)
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
	auto* device = m_graphics->GetInstance()->GetDeviceResources()->GetD3DDevice();

	// テクスチャをロードする
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\standing.png", nullptr, m_standing.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, 	L"Resources\\Image\\jumping.png", nullptr, m_jumping.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\downing.png", nullptr, m_downing.GetAddressOf());

	// プレイヤの初期状態を「立ち」に設定する
	m_currentState = State::STANDING_STATE;
}

// 更新する
void Mario::Update(const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// プレイヤの状態に合わせた行動を行う
	switch (m_currentState)
	{
	case State::STANDING_STATE: // 立っている場合
		if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Space))
		{
			// 速度を設定する
			m_vy = -10.0f;
			// プレイヤの状態を「ジャンプ」に設定する
			m_currentState = State::JUMPING_STATE;
		}
		else if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Down))
		{
			// プレイヤの状態を「屈む」に設定する
			m_currentState = DUCKING_STATE;
		}
		// テクスチャを「立ち」に設定する
		m_currentTexture = m_standing;
		break;

	case State::JUMPING_STATE: // ジャンプする状態
		if (m_y == 400.0f)
		{
			// プレイヤの状態を「立ち」に設定する
			m_currentState = State::STANDING_STATE;
		}
		// テクスチャを「ジャンプ」に設定する
		m_currentTexture = m_jumping;
		break;

	case State::DUCKING_STATE: // 屈む場合
		if (keyboardStateTracker.IsKeyReleased(DirectX::Keyboard::Keys::Down))
		{
			// プレイヤの状態を「立ち」に設定する
			m_currentState = State::STANDING_STATE;
		}
		// テクスチャを「屈む」に設定する
		m_currentTexture = m_downing;
		break;
	}

	// 速度に加速度を加算する
	m_vx += m_ax;
	m_vy += m_ay;

	// 位置に速度を加算する
	m_x += m_vx;
	m_y += m_vy;

	// 地面を判定する
	if (m_y > 400.0f)
	{
		m_y = 400.0f;
		m_vy = 0.0f;
	}
}

// 描画する
void Mario::Render()
{
	// スプライトバッチを開始する
	m_graphics->GetSpriteBatch()->Begin();
	// スプライトを描画する
	m_graphics->GetSpriteBatch()->Draw(m_currentTexture.Get(), DirectX::SimpleMath::Vector2(m_x, m_y));
	// スプライトバッチを終了する
	m_graphics->GetSpriteBatch()->End();
}
