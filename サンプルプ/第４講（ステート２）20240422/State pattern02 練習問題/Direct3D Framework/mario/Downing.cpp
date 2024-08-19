#include "pch.h"
#include "Downing.h"

class Mario;

// コンストラクタ
Downing::Downing(Mario* mario)
	:
	m_mario(mario),
	m_downingTexture(m_mario->GetDowningTexture())
{
}

// デストラクタ
Downing::~Downing()
{
}

// 「屈む」状態を初期化する 
void Downing::Initialize()
{
}

// 「屈む」状態を更新する 
void Downing::Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// ②「↓」キーを解放した場合
	if (keyboardStateTracker.IsKeyReleased(DirectX::Keyboard::Keys::Down))
	{
		// 「立つ」状態に遷移する
		m_mario->ChangeState(m_mario->GetStanding());
	}
}

// 「屈む」状態を描画する 
void Downing::Render()
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

	m_graphics->GetSpriteBatch()->Begin();
	// スプライトを描画する
	m_graphics->GetSpriteBatch()->Draw(
		m_downingTexture,
		m_mario->GetPosition(),
		nullptr,
		DirectX::Colors::White,
		rotation,
		origin,
		scale,
		effects
	);
	m_graphics->GetSpriteBatch()->End();
}

// 後処理をする 
void Downing::Finalize()
{
}
