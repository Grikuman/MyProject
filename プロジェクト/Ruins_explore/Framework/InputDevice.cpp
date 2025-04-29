/*
	ファイル名：InputDevice.cpp
	　　　概要：入力デバイスを管理するクラス
*/
#include "pch.h"
#include "Framework/InputDevice.h"

// シングルトンパターンを実装するための静的メンバ変数
// 初回の GetInstance() 呼び出し時にインスタンスを作成し、それ以降は同じインスタンスを返す
std::unique_ptr<InputDevice> InputDevice::m_InputDevice = nullptr;

//---------------------------------------------------------
// グラフィックスのインスタンスを取得
//---------------------------------------------------------
InputDevice* const InputDevice::GetInstance()
{
	if (m_InputDevice == nullptr)
	{
		m_InputDevice.reset(new InputDevice());
	}
	return m_InputDevice.get();
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
InputDevice::InputDevice()
	:
	m_keyboard{},             
	m_keyboardState{},        
	m_keyboardStateTracker{},
	m_mouse{},
	m_mouseState{},
	m_mouseButtonStateTracker{}
{
	
}

//---------------------------------------------------------
// リソースを読み込む
// シングルトンインスタンスの初回取得時のみ呼び出す
//---------------------------------------------------------
void InputDevice::CreateDevice()
{
	// キーボードを生成する
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardState = std::make_unique<DirectX::Keyboard::State>();
    m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	// マウスを生成する
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouseState = std::make_unique<DirectX::Mouse::State>();
	m_mouseButtonStateTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void InputDevice::Update()
{
	// キーボードを更新する
	UpdateKeyboardState();
	// マウスを更新する
	UpdateMouseState();
}

//---------------------------------------------------------
// キーボードを更新する
//---------------------------------------------------------
void InputDevice::UpdateKeyboardState()
{
	*m_keyboardState = m_keyboard->GetState();
	m_keyboardStateTracker->Update(*m_keyboardState);
}

//---------------------------------------------------------
// マウスを更新する
//---------------------------------------------------------
void InputDevice::UpdateMouseState()
{
	*m_mouseState = m_mouse->GetState();
	m_mouseButtonStateTracker->Update(*m_mouseState);
}

