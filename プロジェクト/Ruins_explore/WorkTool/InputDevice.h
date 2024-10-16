#pragma once
#ifndef InputDevice_DEFINED
#define InputDevice_DEFINED

class InputDevice final
{
public:
	//インプットデバイスのインスタンス取得
	static InputDevice* const GetInstance();

	// キーボードのインスタンスを取得する
	DirectX::Keyboard* GetKeyboard()                                                 { return m_keyboard.get(); }
	// キーボードステートトラッカーのインスタンスを取得する
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()               { return m_keyboardStateTracker.get(); }
	// キーボードステートのインスタンスを取得する
	DirectX::Keyboard::State* GetKeyboardState()                                     { return m_keyboardState.get(); }

private:
	// キーボードを更新する
	void UpdateKeyboardState();
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

public:
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// デストラクタ
	~InputDevice() = default;

private:
	// インプットデバイス
	static std::unique_ptr<InputDevice>                                          m_InputDevice;
	
	// キーボード
	std::unique_ptr<DirectX::Keyboard>                                        m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>                  m_keyboardStateTracker;
	std::unique_ptr<DirectX::Keyboard::State>                                 m_keyboardState;
};

#endif		// InputDevice_DEFINED
