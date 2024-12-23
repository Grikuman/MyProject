/*
	�t�@�C�����FInputDevice.cpp
	�@�@�@�T�v�F���͂��Ǘ�����N���X
*/
#include "pch.h"
#include "WorkTool/InputDevice.h"

std::unique_ptr<InputDevice> InputDevice::m_InputDevice = nullptr;

//�O���t�B�b�N�X�̃C���X�^���X���擾
InputDevice* const InputDevice::GetInstance()
{
	if (m_InputDevice == nullptr)
	{
		m_InputDevice.reset(new InputDevice());
	}
	return m_InputDevice.get();
}

// �R���X�g���N�^
InputDevice::InputDevice()
	:
	m_keyboard{},             
	m_keyboardState{},        
	m_keyboardStateTracker{},
	m_mouse{},
	m_mouseState{},
	m_mouseStateTracker{}
{
	
}

// ����������
void InputDevice::Initialize()
{
	// �L�[�{�[�h�𐶐�����
	m_keyboard             = std::make_unique<DirectX::Keyboard>();
	m_keyboardState        = std::make_unique<DirectX::Keyboard::State>();
    m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	// �}�E�X�𐶐�����
	m_mouse                = std::make_unique<DirectX::Mouse>();
	m_mouseState           = std::make_unique<DirectX::Mouse::State>();
	m_mouseStateTracker    = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

// �X�V����
void InputDevice::Update()
{
	// �L�[�{�[�h���X�V����
	UpdateKeyboardState();
	// �}�E�X���X�V����
	UpdateMouseState();
}

// �L�[�{�[�h���X�V����
void InputDevice::UpdateKeyboardState()
{
	*m_keyboardState = m_keyboard->GetState();
	m_keyboardStateTracker->Update(*m_keyboardState);
}

// �}�E�X���X�V����
void InputDevice::UpdateMouseState()
{
	*m_mouseState = m_mouse->GetState();
	m_mouseStateTracker->Update(*m_mouseState);
}

