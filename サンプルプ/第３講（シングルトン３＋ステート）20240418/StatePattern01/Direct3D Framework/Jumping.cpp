#include "pch.h"
#include "Jumping.h"

class PlayScene;

// コンストラクタ
Jumping::Jumping(Mario* mario)
	:
	m_mario(mario),
	m_jumpingTexture(m_mario->GetJumpingTexture())
{
}

// デストラクタ
Jumping::~Jumping()
{
}

// 「ジャンプ」を初期化する 
void Jumping::Initialize()
{
}

// 「ジャンプ」を更新する 
void Jumping::Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	//速度に加速度を加算する
	m_mario->SetVelocity(m_mario->GetVelocity() + m_mario->GetAcceleration());
	//位置に速度を加算する
	m_mario->SetPosition(m_mario->GetPosition() + m_mario->GetVelocity());

	//空中にいる場合
	if (m_mario->GetPosition().y > PlayScene::GROUND)
	{
		//位置を取得する
		DirectX::SimpleMath::Vector2 position = m_mario->GetPosition();
		//地面の高さを設定
		position.y = PlayScene::GROUND;
		//位置を設定
		m_mario->SetPosition(position);
		//速度を設定する
		DirectX::SimpleMath::Vector2 velocity = m_mario->GetVelocity();
		//速度(VY)を設定
		velocity.y = 0.0f;
		//速度を設定する
		m_mario->SetVelocity(velocity);
	}
	//地面に着地した場合
	if (floor(m_mario->GetPosition().y) == PlayScene::GROUND)
	{
		DirectX::Keyboard::State keyboardState = keyboardStateTracker.GetLastState();

		//「→」キーを押し下げている場合右方向に走る
		if (keyboardState.IsKeyDown(DirectX::Keyboard::Right))
		{
			// 右向きを設定する
			//m_mario->SetDirection(Direction::RIGHT);
			// 現在の状態を「走る」状態に遷移する
			//m_mario->ChangeState(m_mario->GetRunning());
		}
		//「←」キーを押し下げている場合左方向に走る
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::Left))
		{
			// 左向きを設定する
			//m_mario->SetDirection(Direction::LEFT);
			// 現在の状態を「走る」状態に遷移する
			//m_mario->ChangeState(m_mario->GetRunning());
		}
		else
		{
			// 「←」「→」キーを解放した場合に現在の状態を「立ち」状態に遷移する
			m_mario->ChangeState(m_mario->GetStanding());
		}
	}
}

// 「ジャンプ」を描画する 
void Jumping::Render()
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

	m_graphics->GetSpriteBatch()->Begin();
	// スプライトを描画する
	m_graphics->GetSpriteBatch()->Draw(
		m_jumpingTexture,
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
void Jumping::Finalize()
{
}
