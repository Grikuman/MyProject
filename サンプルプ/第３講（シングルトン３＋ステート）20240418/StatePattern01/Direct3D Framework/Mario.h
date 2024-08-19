#pragma once
#ifndef MARIO_DEFINED
#define MARIO_DEFINED

#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "Graphics.h"
#include "IState.h"
#include "Standing.h"
#include "Downing.h"
#include "Jumping.h"

class Standing;
class Downing;
class Jumping;
class PlayScene;

class Mario
{
public:
	// 立ち状態を取得する
	Standing* GetStanding() { return m_standing.get(); }
	// 屈む状態を取得する
	Downing* GetDowning() { return m_downing.get(); }
	// ジャンプ状態を取得する
	Jumping* GetJumping() { return m_jumping.get(); }
	// スタンディングテクスチャを取得する
	ID3D11ShaderResourceView* GetStandingTexture() const { return m_standingTexture.Get(); }
	// ダウンイングテクスチャを取得する
	ID3D11ShaderResourceView* GetDowningTexture() const { return m_downingTexture.Get(); }
	// ジャンピングテクスチャを取得する
	ID3D11ShaderResourceView* GetJumpingTexture() const { return m_jumpingTexture.Get(); }

public:
	// 位置を取得する
	DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	// 速度を取得する
	DirectX::SimpleMath::Vector2 GetVelocity() const { return m_velocity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector2& velocity) { m_velocity = velocity; }
	// 加速度を取得する
	DirectX::SimpleMath::Vector2 GetAcceleration() const { return m_acceleration; }
	// 加速度を設定する
	void SetAcceleration(const DirectX::SimpleMath::Vector2& acceleration) { m_acceleration = acceleration; }

	// 立ち状態に遷移する
	//void ChangeStandingState() { m_currentState = m_standing.get(); }
	// 屈む状態に遷移する
	//void ChangeDowningState() { m_currentState = m_downing.get(); }
	// ジャンプ状態に遷移する
	//void ChangeJumpingstate() { m_currentState = m_jumping.get(); }
	// 状態を遷移する
	void ChangeState(IState* currentState) { m_currentState = currentState; }

public:
	// コンストラクタ
	Mario(PlayScene* playScene);
	// デストラクタ
	~Mario();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker);
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();

private:
	// プレイシーン
	PlayScene* m_playScene;
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// キーボードステートステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardStateTracker;
	// スタンディング
	std::unique_ptr<Standing> m_standing;
	// ダウニイング
	std::unique_ptr<Downing> m_downing;
	// ジャンピング
	std::unique_ptr<Jumping> m_jumping;
	// スタンディング
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_standingTexture;
	// ダウニング
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_downingTexture;
	// ジャンピング
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumpingTexture;

	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 速度
	DirectX::SimpleMath::Vector2 m_velocity;
	// 加速度
	DirectX::SimpleMath::Vector2  m_acceleration;
	// 現在の状態
	IState* m_currentState;
};

#endif		// MARIO_DEFINED
