/*
	�t�@�C�����FInputDevice.h
	�@�@�@�T�v�F���͂��Ǘ�����N���X
*/
#pragma once

class InputDevice final
{
public:
	//�C���v�b�g�f�o�C�X�̃C���X�^���X�擾
	static InputDevice* const GetInstance();

	// �L�[�{�[�h�̃C���X�^���X���擾����
	DirectX::Keyboard* GetKeyboard()                                    { return m_keyboard.get(); }
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�̃C���X�^���X���擾����
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()  { return m_keyboardStateTracker.get(); }
	// �L�[�{�[�h�X�e�[�g�̃C���X�^���X���擾����
	DirectX::Keyboard::State* GetKeyboardState()                        { return m_keyboardState.get(); }

public:
	// ����������
	void Initialize();
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
	// �C���v�b�g�f�o�C�X
	static std::unique_ptr<InputDevice>                      m_InputDevice;
	
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>                       m_keyboard;
	std::unique_ptr<DirectX::Keyboard::State>                m_keyboardState;
    std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse>                          m_mouse;
	std::unique_ptr<DirectX::Mouse::State>                   m_mouseState;
    std::unique_ptr<DirectX::Mouse::ButtonStateTracker>      m_mouseStateTracker;
};

