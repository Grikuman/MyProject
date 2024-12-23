/*
	ファイル名：InputDevice.cpp
	　　　概要：入力を管理するクラス
*/
#include "pch.h"
#include "WorkTool/InputDevice.h"

std::unique_ptr<InputDevice> InputDevice::m_InputDevice = nullptr;

//グラフィックスのインスタンスを取得
InputDevice* const InputDevice::GetInstance()
{
	if (m_InputDevice == nullptr)
	{
		m_InputDevice.reset(new InputDevice());
	}
	return m_InputDevice.get();
}

// コンストラクタ
InputDevice::InputDevice()
	:
	m_keyboard{},             
	m_keyboardState{},        
	m_keyboardStateTracker{},
	m_mouse{},
	m_mouseState{},
	m_mouseStateTracker{}
{
	
}

// 初期化する
void InputDevice::Initialize()
{
	// キーボードを生成する
	m_keyboard             = std::make_unique<DirectX::Keyboard>();
	m_keyboardState        = std::make_unique<DirectX::Keyboard::State>();
    m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	// マウスを生成する
	m_mouse                = std::make_unique<DirectX::Mouse>();
	m_mouseState           = std::make_unique<DirectX::Mouse::State>();
	m_mouseStateTracker    = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

// 更新する
void InputDevice::Update()
{
	// キーボードを更新する
	UpdateKeyboardState();
	// マウスを更新する
	UpdateMouseState();
}

// キーボードを更新する
void InputDevice::UpdateKeyboardState()
{
	*m_keyboardState = m_keyboard->GetState();
	m_keyboardStateTracker->Update(*m_keyboardState);
}

// マウスを更新する
void InputDevice::UpdateMouseState()
{
	*m_mouseState = m_mouse->GetState();
	m_mouseStateTracker->Update(*m_mouseState);
}

