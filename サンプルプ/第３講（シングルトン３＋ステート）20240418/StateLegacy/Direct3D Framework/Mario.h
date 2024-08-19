#pragma once
#ifndef MARIO_DEFINED
#define MARIO_DEFINED

#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "Graphics.h"

class Mario
{
	// プレイヤーの状態
	enum State
	{
		STANDING_STATE,
		JUMPING_STATE,
		DUCKING_STATE,
	};

public:
	// コンストラクタ
	Mario(float x, float y);
	// デストラクタ
	~Mario();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker);
	// 描画する
	void Render();

private:
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();

	// スタンディング
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_standing;
	// ジャンプ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumping;
	// ダウニング
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_downing;
	// 現在のテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_currentTexture;

	// 表示位置
	float m_x, m_y;
	// 速度
	float m_vx, m_vy;
	// 加速度
	float m_ax, m_ay;
	// プレイヤーの状態
	State m_currentState;
};

#endif		// MARIO_DEFINED
