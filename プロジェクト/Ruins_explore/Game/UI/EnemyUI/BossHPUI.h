/*
	ファイル名：BossHPUI.h
	　　　概要：ボスの体力UIを管理するクラス
*/

#pragma once
#include "StepTimer.h"
#include "UserInterface.h"
#include "Framework/DeviceResources.h"
#include <vector>
#include "Keyboard.h"

class BossHPUI
{
public:
	// コンストラクタ
	BossHPUI();
	// デストラクタ
	~BossHPUI();
	// 初期化する
	void Initialize(DX::DeviceResources* pDR, int width, int height);
	// 更新する
	void Update(float bossHP, float MAX_BossHP);
	//描画する
	void Render();
	// 追加する
	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);
private:
	unsigned int m_menuIndex;
	DX::DeviceResources* m_pDR;
	std::unique_ptr<UserInterface> m_BossHPUI;
	std::unique_ptr<UserInterface> m_frame;
	std::unique_ptr<UserInterface> m_base;
	const wchar_t* m_baseTexturePath;
	std::unique_ptr<UserInterface> m_baseWindow;
	int m_windowWidth, m_windowHeight;
	DirectX::Keyboard::KeyboardStateTracker m_tracker;

	// スプライトバッチ
	DirectX::SpriteBatch* m_spriteBatch;
	// スプライトフォント
	DirectX::SpriteFont* m_spriteFont;
	// ボスの現在の体力
	float m_currentHP;
	// ボスの最大体力
	float m_maxHP;
};