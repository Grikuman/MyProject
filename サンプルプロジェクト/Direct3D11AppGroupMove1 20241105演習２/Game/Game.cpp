#include "Framework/pch.h"
#include "Game.h"
#include "Graphics.h"
#include "Camera.h"

extern void ExitGame() noexcept;

using Microsoft::WRL::ComPtr;

// コンストラクタ
Game::Game() noexcept(false)
	:
	m_hWnd{},												// ウィンドウハンドル
	m_graphics{},										// グラフィックス
	m_deviceResources{},						// デバイスリソース
	m_timer{},												// タイマー
	m_keyboard{},										// キーボード
	m_keyboardStateTracker{},			// キーボードステートトラッカー
	m_camera{},											// カメラ
	m_eyePosition{},								// 視点
	m_playScene{}									// プレイシーン
{
	// グラフィックスのインスタンスを取得する
	m_graphics = Graphics::GetInstance();
	// デバイスリソースを取得する
	m_deviceResources = m_graphics->GetDeviceResources();
	// デバイスの通知先を設定する
    m_deviceResources->RegisterDeviceNotify(this);
}

// Direct3Dリソースを初期化する
void Game::Initialize(HWND window, int width, int height)
{
	// ウィンドウハンドルを設定する
	m_hWnd = window;
	// デバイスリソースに「ウィンドウハンドル」「幅」「高さ」を設定する
    m_deviceResources->SetWindow(window, width, height);
	 // デバイスリソースを生成する
    m_deviceResources->CreateDeviceResources();
	 // デバイスに依存したリソースを生成する
    CreateDeviceDependentResources();
	 // ウィンドウサイズに依存したリソースを生成する
    m_deviceResources->CreateWindowSizeDependentResources();
	 // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();

    // タイマー設定を変更する
    m_timer.SetFixedTimeStep(true);
	 // タイマーにターゲット経過秒(60FPS)を設定する
    m_timer.SetTargetElapsedSeconds(1.0 / 60);

	 // マウスのインスタンスを生成する
	 m_mouse = std::make_unique<DirectX::Mouse>();
	 // ウィンドウサイズを設定する
	 m_mouse->SetWindow(window);
	 // キーボードのインスタンスを生成する
	 m_keyboard = std::make_unique<DirectX::Keyboard>();
	 // キーボードトラッカーのインスタンスを生成する
	 m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	 // 画面サイズ
	 int screenWidth, screenHeight;
	 // 画面サイズを取得する
	 GetDefaultSize(screenWidth, screenHeight);
	 // 画面サイズを設定する
	 m_graphics->SetScreenSize(screenWidth, screenHeight);
	 // カメラを生成する
	 m_camera = std::make_unique<Camera>(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 258.0f));
	 // 射影行列を生成する
	 DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		 DirectX::XMConvertToRadians(45.0f),
		 screenWidth / (float)screenHeight,
		 0.1f,
		 1000.0f
	 );
	 // 射影行列を設定する
	 m_graphics->SetProjectionMatrix(projection);
	 // PlaySceneクラスのインスタンスを生成する
	 m_playScene = std::make_unique<PlayScene>(this);
	 // PlaySceneクラスのインスタンスを初期化する
	 m_playScene->Initialize();
}

#pragma region Frame Update
// ゲームループを実行する
void Game::Tick()
{
	m_timer.Tick([&]() { Update(m_timer); });
	// 描画する
    Render();
}

// ワールドを更新する
void Game::Update(const DX::StepTimer& timer)
{
	// カメラを更新する
	m_camera->Update();
	// プレイシーンを更新する
	 m_playScene->Update(timer);
}
#pragma endregion

#pragma region Frame Render
// シーンを描画する
void Game::Render()
{
    // 描画可能でない場合は復帰する
    if (m_timer.GetFrameCount() == 0) { return; }
	 // バックバッファをクリアする
    Clear();
	 // PIX開始イベント
    m_deviceResources->PIXBeginEvent(L"Render");
	 // プレイシーンを描画する
	 m_playScene->Render();
	// PIX終了イベント
    m_deviceResources->PIXEndEvent();
    // 新規フレームを描画する
    m_deviceResources->Present();
}

// バックバッファをクリアする
void Game::Clear()
{
	// PIX開始イベント
    m_deviceResources->PIXBeginEvent(L"Clear");
    // ビューをクリアする
    auto context = m_deviceResources->GetD3DDeviceContext();
	 // レンダーターゲットを取得する
    auto renderTarget = m_deviceResources->GetRenderTargetView();
	 // 深度ステンシルビューを取得する
    auto depthStencil = m_deviceResources->GetDepthStencilView();
	 // レンダーターゲットビューをクリアする
    context->ClearRenderTargetView(renderTarget, DirectX::Colors::Gray);
	 // 深度ステンシルビューをクリアする
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	 // レンダーターゲットを設定する
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // スクリーンビューポートを取得する
    auto viewport = m_deviceResources->GetScreenViewport();
	 // ビューポートを設定する
    context->RSSetViewports(1, &viewport);
	 // PIX終了イベント
    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// メッセージハンドラ
void Game::OnActivated()
{
    // ゲームがアクティブウィンドウになったときの処理を記述する
}

void Game::OnDeactivated()
{
    // ゲームが背景ウィンドウになった時の処理を記述する
}

void Game::OnSuspending()
{
    // ゲームの実行中に電源が停止した時の処理を記述する
}

void Game::OnResuming()
{
	// 経過時間をリセットする
	m_timer.ResetElapsedTime();

	// ゲームの実行中に電源が復帰した時の処理を記述する
}

// ウィンドウが移動したときの処理を記述する
void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

// ウィンドウサイズが変更された時の処理を記述する
void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;
	// ウィンドウサイズに依存したリソースを生成する
	CreateWindowSizeDependentResources();

	// ゲームウィンドウのサイズが変更された時の処理を記述する
}

// 規定ウィンドウサイズを取得する
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
	// 規定のウィンドウサイズ
	width = 1440;
	height = 900;
}
#pragma endregion

#pragma region Direct3D Resources
// デバイスに依存したリソースを生成する
void Game::CreateDeviceDependentResources()
{
   // デバイスに依存したオブジェクトを初期化する
	int width, height;
	// ウィンドウの既定サイズを取得する
	GetDefaultSize(width, height);
	// 「ウィンドウハンドル」「幅」「高さ」を設定する
	m_graphics->GetDeviceResources()->SetWindow(m_hWnd, width, height);
	// グラフィックスを初期化する
	m_graphics->Initialize();
}

// ウィンドウサイズが変更されたイベントによりメモリリソースを確保する
void Game::CreateWindowSizeDependentResources()
{
	// ウィンドウサイズに依存したオブジェクトを初期化するコードを記述する
	// 出力サイズを取得する
	auto m_size = m_deviceResources->GetOutputSize();
	// アスペクト率を計算する
	float aspectRatio = float(m_size.right) / float(m_size.bottom);
	// 視野角を設定する
	float fovAngleY = 45.0f * DirectX::XM_PI / 180.0f;
	// アプリが縦向きまたはスナップビューのときに変更する
	if (aspectRatio < 1.0f) { 	fovAngleY *= 2.0f; }
	// 射影行列を生成する
	DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView	(
		fovAngleY,
		aspectRatio,
		0.1f,
		1000.0f
	);
	// 射影行列を設定する
	m_graphics->SetProjectionMatrix(projection);
	// アークボールのウィンドウサイズを設定する
	if (m_playScene) { m_playScene->SetWindowForArcBall(m_size.right, m_size.bottom); }
}

// デバイスロストが発生した時の処理を記述する
void Game::OnDeviceLost()
{
    // Direct3Dリソースをクリーンアップする処理を記述する
}

// デバイスが復帰した時の処理を記述する
void Game::OnDeviceRestored()
{
	// デバイスに依存したリソースを生成する
    CreateDeviceDependentResources();
	 // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();
}
#pragma endregion
