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
	m_keyboard{},                        // キーボード
	m_keyboardStateTracker{},            // キーボードステートトラッカー
	m_keyboardState{}                    // キーボードステート
{
	
}

// 初期化する
void InputDevice::Initialize()
{
	// キーボードを生成する
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	m_keyboardState = std::make_unique<DirectX::Keyboard::State>();
}

// 更新する
void InputDevice::Update()
{
	// キーボードを更新する
	UpdateKeyboardState();
}

// キーボードを更新する
void InputDevice::UpdateKeyboardState()
{
	*m_keyboardState = m_keyboard->GetState();
	m_keyboardStateTracker->Update(*m_keyboardState);
}

