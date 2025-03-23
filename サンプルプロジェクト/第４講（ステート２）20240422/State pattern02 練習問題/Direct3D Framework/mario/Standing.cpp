#include "pch.h"
#include "Standing.h"

class PlayScene;

// コンストラクタ
Standing::Standing(Mario* mario)
	:
	m_mario(mario),
	m_standingTexture(m_mario->GetStandingTexture())
{
}

// デストラクタ
Standing::~Standing()
{
}

// 初期化する 
void Standing::Initialize()
{
}

// 更新する 
void Standing::Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// 速度を初期化する
	DirectX::SimpleMath::Vector2 velocity = DirectX::SimpleMath::Vector2::Zero;

	// ②「↓」キーを押し下げた場合「屈む」状態に遷移する
	if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Down))
	{
		// 「屈む」状態に遷移する
		m_mario->ChangeState(m_mario->GetDowning());
	}
	// ⑤「Space」キーを押し下げた場合「ジャンプ」状態に遷移する
	if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Space))
	{
		// 速度に初期値(0.0f, -15.0f)を設定する
		m_mario->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, -15.0f));
		// 「ジャンプ」状態に遷移する
		m_mario->ChangeState(m_mario->GetJumping());
	}
	// ③「→」キーを押し下げた場合「走る」状態に遷移する
	else if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Right))
	{
		// 速度(VX)を取得する 
		velocity = m_mario->GetVelocity();
		// 速度(VX)を設定する
		velocity.x = 5.0;
		// 速度(VX)を設定する 
		m_mario->SetVelocity(velocity);
		// 向きを右に変更する
		m_mario->SetDirection(Direction::RIGHT);
		// プレイヤの状態を「ランニング」状態に遷移する
		;
	}
	// ③「←」キーを押し下げた場合「走る」状態に遷移する
	else if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Left))
	{
		// 速度(VX)を取得する 
		velocity = m_mario->GetVelocity();
		// 速度(VX)を設定する
		velocity.x = -5.0f;
		// 速度(VX)を設定する 
		m_mario->SetVelocity(velocity);

		// 向きを左に変更する
		m_mario->SetDirection(Direction::LEFT);
		// プレイヤの状態を「ランニング」状態に遷移する
		;
	}
}

// 描画する
void Standing::Render()
{
	// 回転を設定する
	float rotation = 0.0f;
	// スケールを設定する
	float scale = 1.0f;
	// 原点を設定する
	const DirectX::SimpleMath::Vector2 origin = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	// スプライト効果を設定しない 
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
	// 水平方向に反転させる
	if (m_mario->GetDirection() == Direction::LEFT)
	{
		// 水平方向に反転させる
		effects = DirectX::SpriteEffects_FlipHorizontally;
	}
	// スプライトバッチを開始する
	m_graphics->GetSpriteBatch()->Begin();
	// スプライトを描画する
	m_graphics->GetSpriteBatch()->Draw(
		m_standingTexture,
		m_mario->GetPosition(),
		nullptr,
		DirectX::Colors::White,
		rotation,
		origin,
		scale,
		effects
	);
	// スプライトバッチを終了する
	m_graphics->GetSpriteBatch()->End();
}

// 後処理をする
void Standing::Finalize()
{
}
