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

// 「立ち」状態を初期化する 
void Standing::Initialize()
{
}

// 「立ち」状態を更新する 
void Standing::Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// ②「↓」キーを解放した場合「屈む」状態に遷移する
	if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Down))
	{
		// 「屈む」状態状態に変更する
		m_mario->ChangeState(m_mario->GetDowning());
	}
}

// 「立ち」状態を描画する
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
	//effects = DirectX::SpriteEffects_FlipHorizontally;
	// スプライトバッチを取得する
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
	m_graphics->GetSpriteBatch()->End();
}

// 後処理をする
void Standing::Finalize()
{
}
