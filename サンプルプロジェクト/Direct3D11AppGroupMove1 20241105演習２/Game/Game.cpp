#include "Framework/pch.h"
#include "Game.h"
#include "Graphics.h"
#include "Camera.h"

extern void ExitGame() noexcept;

using Microsoft::WRL::ComPtr;

// �R���X�g���N�^
Game::Game() noexcept(false)
	:
	m_hWnd{},												// �E�B���h�E�n���h��
	m_graphics{},										// �O���t�B�b�N�X
	m_deviceResources{},						// �f�o�C�X���\�[�X
	m_timer{},												// �^�C�}�[
	m_keyboard{},										// �L�[�{�[�h
	m_keyboardStateTracker{},			// �L�[�{�[�h�X�e�[�g�g���b�J�[
	m_camera{},											// �J����
	m_eyePosition{},								// ���_
	m_playScene{}									// �v���C�V�[��
{
	// �O���t�B�b�N�X�̃C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �f�o�C�X���\�[�X���擾����
	m_deviceResources = m_graphics->GetDeviceResources();
	// �f�o�C�X�̒ʒm���ݒ肷��
    m_deviceResources->RegisterDeviceNotify(this);
}

// Direct3D���\�[�X������������
void Game::Initialize(HWND window, int width, int height)
{
	// �E�B���h�E�n���h����ݒ肷��
	m_hWnd = window;
	// �f�o�C�X���\�[�X�Ɂu�E�B���h�E�n���h���v�u���v�u�����v��ݒ肷��
    m_deviceResources->SetWindow(window, width, height);
	 // �f�o�C�X���\�[�X�𐶐�����
    m_deviceResources->CreateDeviceResources();
	 // �f�o�C�X�Ɉˑ��������\�[�X�𐶐�����
    CreateDeviceDependentResources();
	 // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    m_deviceResources->CreateWindowSizeDependentResources();
	 // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    CreateWindowSizeDependentResources();

    // �^�C�}�[�ݒ��ύX����
    m_timer.SetFixedTimeStep(true);
	 // �^�C�}�[�Ƀ^�[�Q�b�g�o�ߕb(60FPS)��ݒ肷��
    m_timer.SetTargetElapsedSeconds(1.0 / 60);

	 // �}�E�X�̃C���X�^���X�𐶐�����
	 m_mouse = std::make_unique<DirectX::Mouse>();
	 // �E�B���h�E�T�C�Y��ݒ肷��
	 m_mouse->SetWindow(window);
	 // �L�[�{�[�h�̃C���X�^���X�𐶐�����
	 m_keyboard = std::make_unique<DirectX::Keyboard>();
	 // �L�[�{�[�h�g���b�J�[�̃C���X�^���X�𐶐�����
	 m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	 // ��ʃT�C�Y
	 int screenWidth, screenHeight;
	 // ��ʃT�C�Y���擾����
	 GetDefaultSize(screenWidth, screenHeight);
	 // ��ʃT�C�Y��ݒ肷��
	 m_graphics->SetScreenSize(screenWidth, screenHeight);
	 // �J�����𐶐�����
	 m_camera = std::make_unique<Camera>(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 258.0f));
	 // �ˉe�s��𐶐�����
	 DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		 DirectX::XMConvertToRadians(45.0f),
		 screenWidth / (float)screenHeight,
		 0.1f,
		 1000.0f
	 );
	 // �ˉe�s���ݒ肷��
	 m_graphics->SetProjectionMatrix(projection);
	 // PlayScene�N���X�̃C���X�^���X�𐶐�����
	 m_playScene = std::make_unique<PlayScene>(this);
	 // PlayScene�N���X�̃C���X�^���X������������
	 m_playScene->Initialize();
}

#pragma region Frame Update
// �Q�[�����[�v�����s����
void Game::Tick()
{
	m_timer.Tick([&]() { Update(m_timer); });
	// �`�悷��
    Render();
}

// ���[���h���X�V����
void Game::Update(const DX::StepTimer& timer)
{
	// �J�������X�V����
	m_camera->Update();
	// �v���C�V�[�����X�V����
	 m_playScene->Update(timer);
}
#pragma endregion

#pragma region Frame Render
// �V�[����`�悷��
void Game::Render()
{
    // �`��\�łȂ��ꍇ�͕��A����
    if (m_timer.GetFrameCount() == 0) { return; }
	 // �o�b�N�o�b�t�@���N���A����
    Clear();
	 // PIX�J�n�C�x���g
    m_deviceResources->PIXBeginEvent(L"Render");
	 // �v���C�V�[����`�悷��
	 m_playScene->Render();
	// PIX�I���C�x���g
    m_deviceResources->PIXEndEvent();
    // �V�K�t���[����`�悷��
    m_deviceResources->Present();
}

// �o�b�N�o�b�t�@���N���A����
void Game::Clear()
{
	// PIX�J�n�C�x���g
    m_deviceResources->PIXBeginEvent(L"Clear");
    // �r���[���N���A����
    auto context = m_deviceResources->GetD3DDeviceContext();
	 // �����_�[�^�[�Q�b�g���擾����
    auto renderTarget = m_deviceResources->GetRenderTargetView();
	 // �[�x�X�e���V���r���[���擾����
    auto depthStencil = m_deviceResources->GetDepthStencilView();
	 // �����_�[�^�[�Q�b�g�r���[���N���A����
    context->ClearRenderTargetView(renderTarget, DirectX::Colors::Gray);
	 // �[�x�X�e���V���r���[���N���A����
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	 // �����_�[�^�[�Q�b�g��ݒ肷��
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // �X�N���[���r���[�|�[�g���擾����
    auto viewport = m_deviceResources->GetScreenViewport();
	 // �r���[�|�[�g��ݒ肷��
    context->RSSetViewports(1, &viewport);
	 // PIX�I���C�x���g
    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// ���b�Z�[�W�n���h��
void Game::OnActivated()
{
    // �Q�[�����A�N�e�B�u�E�B���h�E�ɂȂ����Ƃ��̏������L�q����
}

void Game::OnDeactivated()
{
    // �Q�[�����w�i�E�B���h�E�ɂȂ������̏������L�q����
}

void Game::OnSuspending()
{
    // �Q�[���̎��s���ɓd������~�������̏������L�q����
}

void Game::OnResuming()
{
	// �o�ߎ��Ԃ����Z�b�g����
	m_timer.ResetElapsedTime();

	// �Q�[���̎��s���ɓd�������A�������̏������L�q����
}

// �E�B���h�E���ړ������Ƃ��̏������L�q����
void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

// �E�B���h�E�T�C�Y���ύX���ꂽ���̏������L�q����
void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;
	// �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
	CreateWindowSizeDependentResources();

	// �Q�[���E�B���h�E�̃T�C�Y���ύX���ꂽ���̏������L�q����
}

// �K��E�B���h�E�T�C�Y���擾����
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
	// �K��̃E�B���h�E�T�C�Y
	width = 1440;
	height = 900;
}
#pragma endregion

#pragma region Direct3D Resources
// �f�o�C�X�Ɉˑ��������\�[�X�𐶐�����
void Game::CreateDeviceDependentResources()
{
   // �f�o�C�X�Ɉˑ������I�u�W�F�N�g������������
	int width, height;
	// �E�B���h�E�̊���T�C�Y���擾����
	GetDefaultSize(width, height);
	// �u�E�B���h�E�n���h���v�u���v�u�����v��ݒ肷��
	m_graphics->GetDeviceResources()->SetWindow(m_hWnd, width, height);
	// �O���t�B�b�N�X������������
	m_graphics->Initialize();
}

// �E�B���h�E�T�C�Y���ύX���ꂽ�C�x���g�ɂ�胁�������\�[�X���m�ۂ���
void Game::CreateWindowSizeDependentResources()
{
	// �E�B���h�E�T�C�Y�Ɉˑ������I�u�W�F�N�g������������R�[�h���L�q����
	// �o�̓T�C�Y���擾����
	auto m_size = m_deviceResources->GetOutputSize();
	// �A�X�y�N�g�����v�Z����
	float aspectRatio = float(m_size.right) / float(m_size.bottom);
	// ����p��ݒ肷��
	float fovAngleY = 45.0f * DirectX::XM_PI / 180.0f;
	// �A�v�����c�����܂��̓X�i�b�v�r���[�̂Ƃ��ɕύX����
	if (aspectRatio < 1.0f) { 	fovAngleY *= 2.0f; }
	// �ˉe�s��𐶐�����
	DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView	(
		fovAngleY,
		aspectRatio,
		0.1f,
		1000.0f
	);
	// �ˉe�s���ݒ肷��
	m_graphics->SetProjectionMatrix(projection);
	// �A�[�N�{�[���̃E�B���h�E�T�C�Y��ݒ肷��
	if (m_playScene) { m_playScene->SetWindowForArcBall(m_size.right, m_size.bottom); }
}

// �f�o�C�X���X�g�������������̏������L�q����
void Game::OnDeviceLost()
{
    // Direct3D���\�[�X���N���[���A�b�v���鏈�����L�q����
}

// �f�o�C�X�����A�������̏������L�q����
void Game::OnDeviceRestored()
{
	// �f�o�C�X�Ɉˑ��������\�[�X�𐶐�����
    CreateDeviceDependentResources();
	 // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    CreateWindowSizeDependentResources();
}
#pragma endregion
