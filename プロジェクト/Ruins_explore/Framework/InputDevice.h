/*
	�t�@�C�����FInputDevice.h
	�@�@�@�T�v�F���̓f�o�C�X���Ǘ�����N���X
*/
#pragma once

class InputDevice final
{
public:
	//�C���v�b�g�f�o�C�X�̃C���X�^���X�擾
	static InputDevice* const GetInstance();

	// �L�[�{�[�h�̃C���X�^���X���擾����
	DirectX::Keyboard* GetKeyboard() { return m_keyboard.get(); }
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�̃C���X�^���X���擾����
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_keyboardStateTracker.get(); }
	// �L�[�{�[�h�X�e�[�g�̃C���X�^���X���擾����
	DirectX::Keyboard::State* GetKeyboardState() { return m_keyboardState.get(); }

	// �}�E�X�̃C���X�^���X���擾����
	DirectX::Mouse* GetMouse() { return m_mouse.get(); }
	// �}�E�X�X�e�[�g�̃C���X�^���X���擾����
	DirectX::Mouse::State* GetMouseState() { return m_mouseState.get(); }
	// �}�E�X�{�^���X�e�[�g�g���b�J�[�̃C���X�^���X���擾����
	DirectX::Mouse::ButtonStateTracker* GetMouseButtonStateTracker() { return m_mouseButtonStateTracker.get(); }

public:
	// �f�o�C�X���쐬����
	void CreateDevice();
	// �X�V����
	void Update();
	// �f�X�g���N�^
	~InputDevice() = default;

private:
	// �L�[�{�[�h���X�V����
	void UpdateKeyboardState();
	// �}�E�X���X�V����
	void UpdateMouseState();

private:
	// �R���X�g���N�^
	InputDevice();
	// �C���X�^���X���R�s�[���邱�Ƃ��֎~����
	void operator=(const InputDevice&) = delete;
	// �C���X�^���X�����[�u���邱�Ƃ��֎~����
	InputDevice& operator= (InputDevice&&) = delete;
	// �R�s�[�R���X�g���N�^�͋֎~����
	InputDevice(const InputDevice&) = delete;
	// ���[�u�R���X�g���N�^�͋֎~����
	InputDevice(InputDevice&&) = delete;

private:
	// �C���v�b�g�f�o�C�X�N���X
	static std::unique_ptr<InputDevice>                      m_InputDevice;
	
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>                       m_keyboard;
	std::unique_ptr<DirectX::Keyboard::State>                m_keyboardState;
    std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse>                          m_mouse;
	std::unique_ptr<DirectX::Mouse::State>                   m_mouseState;
    std::unique_ptr<DirectX::Mouse::ButtonStateTracker>      m_mouseButtonStateTracker;
};

