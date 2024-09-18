//--------------------------------------------------------------------------------------
// File: Gauge.h
//
// ゲージクラス
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include "UserInterface.h"
#include "WorkTool/DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
#include "Keyboard.h"

class Gauge
{
private:
	unsigned int m_menuIndex;
	DX::DeviceResources* m_pDR;

	//std::vector<std::unique_ptr<tito::UserInterface>> m_userInterface;
	//std::vector<std::unique_ptr<tito::UserInterface>> m_base;

	std::unique_ptr<UserInterface> m_gauge;
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

public:
	Gauge();
	~Gauge();

	void Initialize(DX::DeviceResources* pDR, int width, int height);
	void Update(float bossHP,float MAX_BossHP);
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

};