//
//	Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "ImaseLib/DebugFont.h"
#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "ImaseLib/DebugCamera.h"

#include "TitoLib/Particle.h"


//	A basic game implementation that creates a D3D11 device and
//	provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    //	Initialization and management
    void Initialize(HWND window, int width, int height);

    //	Basic game loop
    void Tick();

    //	IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    //	Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    //	Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    std::unique_ptr<Imase::DebugCamera> m_debugCamera;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    //	Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    //	Rendering loop timer.
    DX::StepTimer                           m_timer;

private:

    //	追加
    std::unique_ptr<tito::Particle> m_particles;

    //	キーボードステートトラッカー
    DirectX::Keyboard::KeyboardStateTracker m_tracker;

    //	共通ステートオブジェクトへのポインタ
    std::unique_ptr<DirectX::CommonStates> m_states;

    //	デバッグ用文字列表示オブジェクトへのポインタ
    std::unique_ptr<Imase::DebugFont> m_font;

    //	ユーザーリソースへのポインタ
    std::unique_ptr<UserResources> m_userResources;

    //	シーンマネージャーへのポインタ
    std::unique_ptr<Imase::SceneManager<UserResources>> m_sceneManager;


};
