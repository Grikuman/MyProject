//
//	Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <sstream>
#include "SampleScene.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();

    m_deviceResources->RegisterDeviceNotify(this);

}

//	Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
    m_debugCamera = std::make_unique<Imase::DebugCamera>(width, height);

    //	ユーザーリソースの作成
    m_userResources = std::make_unique<UserResources>();

    //	ユーザーリソースの中身を設定（各シーンに渡したい物を設定）
    m_userResources->SetDeviceResources(m_deviceResources.get());
    m_userResources->SetCommonStates(m_states.get());
    m_userResources->SetKeyboardStateTracker(&m_tracker);
    m_userResources->SetStepTimerStates(&m_timer);
    m_userResources->SetDebugFont(m_font.get());

    //	シーンマネージャーの作成
    m_sceneManager = std::make_unique<Imase::SceneManager<UserResources>>(m_userResources.get());

    //	起動シーンの設定
    m_sceneManager->SetScene<SampleScene>();
}

#pragma region Frame Update
//	Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

//	Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
     
    //	キーボードステートトラッカーを更新
    DirectX::Keyboard::State state = Keyboard::Get().GetState();
    m_tracker.Update(state);

    m_debugCamera->Update();

    //	シーンの更新
    m_sceneManager->Update(elapsedTime);

    //	fpsの表示
    std::wostringstream oss;
    oss << "fps:" << m_timer.GetFramesPerSecond();
    m_font->AddString(oss.str().c_str(), SimpleMath::Vector2(0.0f, 0.0f));
}
#pragma endregion

#pragma region Frame Render
//	Draws the scene.
void Game::Render()
{
    //	Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();

    //	TODO: Add your rendering code here.
    context;

    SimpleMath::Matrix world, view, proj;

    //	ビュー行列の作成
    view = m_debugCamera->GetCameraMatrix();

    //	射影行列の作成
    int width, height;
    GetDefaultSize(width, height);
    proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        XMConvertToRadians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

    //	シーンの描画
    m_sceneManager->Render();

    //  床の描画
    m_floor_Primitive->Render(context, view, proj);

    m_particle->Render(view, proj);
    //	デバッグ用文字列の表示
    m_font->Render(m_states.get());

    m_deviceResources->PIXEndEvent();

    //  Show the new frame.
    m_deviceResources->Present();
}

//	Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    //	Clear the views.
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();
    ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargetView();
    ID3D11DepthStencilView* depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    //	Set the viewport.
    D3D11_VIEWPORT const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
//	Message handlers
void Game::OnActivated()
{

}

void Game::OnDeactivated()
{

}

void Game::OnSuspending()
{

}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();
}

void Game::OnWindowMoved()
{
    RECT const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

//	Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
//	These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    ID3D11Device1* device = m_deviceResources->GetD3DDevice();
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();

    //  床モデルの作成
    m_floor_Primitive = std::make_unique<tito::Floor_Primitive>(device);

    //	共通ステートオブジェクトの作成
    m_states = std::make_unique<CommonStates>(device);
    m_particle = std::make_unique<tito::Particle>();
    m_particle->Create(m_deviceResources.get());

    //	デバッグ用文字列表示オブジェクトの作成
    m_font = std::make_unique<Imase::DebugFont>(device, context, L"Resources/Font/SegoeUI_18.spritefont");
    
    //	シーンのデバイスに依存するオブジェクトの作成
    if (m_sceneManager) m_sceneManager->CreateDeviceDependentResources();
}

//	Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    //	シーンのウインドウサイズに依存するオブジェクトの作成
    if (m_sceneManager) m_sceneManager->CreateWindowSizeDependentResources();
}

void Game::OnDeviceLost()
{
    if (m_sceneManager) m_sceneManager->OnDeviceLost();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
