/*
	ファイル名：InputDevice.h
	　　　概要：入力デバイスを管理するクラス
*/
#pragma once

class InputDevice final
{
public:
	//インプットデバイスのインスタンス取得
	static InputDevice* const GetInstance();

	// キーボードのインスタンスを取得する
	DirectX::Keyboard* GetKeyboard() { return m_keyboard.get(); }
	// キーボードステートトラッカーのインスタンスを取得する
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_keyboardStateTracker.get(); }
	// キーボードステートのインスタンスを取得する
	DirectX::Keyboard::State* GetKeyboardState() { return m_keyboardState.get(); }

	// マウスのインスタンスを取得する
	DirectX::Mouse* GetMouse() { return m_mouse.get(); }
	// マウスステートのインスタンスを取得する
	DirectX::Mouse::State* GetMouseState() { return m_mouseState.get(); }
	// マウスボタンステートトラッカーのインスタンスを取得する
	DirectX::Mouse::ButtonStateTracker* GetMouseButtonStateTracker() { return m_mouseButtonStateTracker.get(); }

public:
	// デバイスを作成する
	void CreateDevice();
	// 更新する
	void Update();
	// デストラクタ
	~InputDevice() = default;

private:
	// キーボードを更新する
	void UpdateKeyboardState();
	// マウスを更新する
	void UpdateMouseState();

private:
	// コンストラクタ
	InputDevice();
	// インスタンスをコピーすることを禁止する
	void operator=(const InputDevice&) = delete;
	// インスタンスをムーブすることを禁止する
	InputDevice& operator= (InputDevice&&) = delete;
	// コピーコンストラクタは禁止する
	InputDevice(const InputDevice&) = delete;
	// ムーブコンストラクタは禁止する
	InputDevice(InputDevice&&) = delete;

private:
	// インプットデバイスクラス
	static std::unique_ptr<InputDevice>                      m_InputDevice;
	
	// キーボード
	std::unique_ptr<DirectX::Keyboard>                       m_keyboard;
	std::unique_ptr<DirectX::Keyboard::State>                m_keyboardState;
    std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// マウス
	std::unique_ptr<DirectX::Mouse>                          m_mouse;
	std::unique_ptr<DirectX::Mouse::State>                   m_mouseState;
    std::unique_ptr<DirectX::Mouse::ButtonStateTracker>      m_mouseButtonStateTracker;
};

