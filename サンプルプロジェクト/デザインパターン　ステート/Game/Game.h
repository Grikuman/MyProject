//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Camera.h"
#include "PlayScene.h"


// D3D11�f�o�C�X�𐶐����Q�[�����[�v��񋟂���Q�[���N���X
class Game final : public DX::IDeviceNotify
{
public:
	// �L�[�{�[�h���擾����
	DirectX::Keyboard* GetKeyboard() const { return m_keyboard.get(); }
	// �L�[�{�[�h�X�e�[�g�g���b�J���擾����
	DirectX::Keyboard::KeyboardStateTracker& GetKeyboardStateTracker() const { return *m_keyboardStateTracker.get(); }
	// �}�E�X���擾����
	DirectX::Mouse* GetMouse() const { return m_mouse.get(); }
	// �J�������擾����
	Camera* GetCamera() const { return m_camera.get(); }

public:
	// �R���X�g���N�^
    Game() noexcept(false);
	 // �f�X�g���N�^
    ~Game() = default;
    Game(Game&&) = default;
    Game& operator= (Game&&) = default;
    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // ����������
    void Initialize(HWND window, int width, int height);

    // �Q�[�����[�v
    void Tick();

    // IDeviceNotify�C���^�[�t�F�[�X
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // ���b�Z�[�W�n���h���[
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // �K��E�B���h�E�T�C�Y�v���p�e�B���擾����
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:
	// �X�V����
    void Update(DX::StepTimer const& timer);
	 // �`�悷��
    void Render();
	 // 
    void Clear();
	 // �f�o�C�X�ˑ��������\�[�X�𐶐�����
    void CreateDeviceDependentResources();
	 // �E�B���h�E�T�C�Y�Ɉˑ��������\�[�X�𐶐�����
    void CreateWindowSizeDependentResources();

private:
	// �E�B���h�E�n���h��
	HWND m_hWnd;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �f�o�C�X���\�[�X
	// std::unique_ptr<DX::DeviceResources>    m_deviceResources;
	DX::DeviceResources* m_deviceResources;
	// �^�C�}�[
	DX::StepTimer  m_timer;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// �L�[�{�[�h�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// �J����
	std::unique_ptr<Camera> m_camera;
	// �J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_eyePosition;
	
	// �v���C�V�[��
	std::unique_ptr<PlayScene> m_playScene;

};
