//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Camera.h"
#include "PlayScene.h"


// D3D11デバイスを生成しゲームループを提供するゲームクラス
class Game final : public DX::IDeviceNotify
{
public:
	// キーボードを取得する
	DirectX::Keyboard* GetKeyboard() const { return m_keyboard.get(); }
	// キーボードステートトラッカを取得する
	DirectX::Keyboard::KeyboardStateTracker& GetKeyboardStateTracker() const { return *m_keyboardStateTracker.get(); }
	// マウスを取得する
	DirectX::Mouse* GetMouse() const { return m_mouse.get(); }
	// カメラを取得する
	Camera* GetCamera() const { return m_camera.get(); }

public:
	// コンストラクタ
    Game() noexcept(false);
	 // デストラクタ
    ~Game() = default;
    Game(Game&&) = default;
    Game& operator= (Game&&) = default;
    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // 初期化する
    void Initialize(HWND window, int width, int height);

    // ゲームループ
    void Tick();

    // IDeviceNotifyインターフェース
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // メッセージハンドラー
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // 規定ウィンドウサイズプロパティを取得する
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:
	// 更新する
    void Update(DX::StepTimer const& timer);
	 // 描画する
    void Render();
	 // 
    void Clear();
	 // デバイス依存したリソースを生成する
    void CreateDeviceDependentResources();
	 // ウィンドウサイズに依存したリソースを生成する
    void CreateWindowSizeDependentResources();

private:
	// ウィンドウハンドル
	HWND m_hWnd;
	// グラフィックス
	Graphics* m_graphics;
	// デバイスリソース
	// std::unique_ptr<DX::DeviceResources>    m_deviceResources;
	DX::DeviceResources* m_deviceResources;
	// タイマー
	DX::StepTimer  m_timer;
	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// キーボードトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// カメラ
	std::unique_ptr<Camera> m_camera;
	// カメラの位置
	DirectX::SimpleMath::Vector3 m_eyePosition;
	
	// プレイシーン
	std::unique_ptr<PlayScene> m_playScene;

};
