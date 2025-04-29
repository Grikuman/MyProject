/*
	�t�@�C�����FInputDevice.cpp
	�@�@�@�T�v�F���̓f�o�C�X���Ǘ�����N���X
*/
#include "pch.h"
#include "Framework/InputDevice.h"

// �V���O���g���p�^�[�����������邽�߂̐ÓI�����o�ϐ�
// ����� GetInstance() �Ăяo�����ɃC���X�^���X���쐬���A����ȍ~�͓����C���X�^���X��Ԃ�
std::unique_ptr<InputDevice> InputDevice::m_InputDevice = nullptr;

//---------------------------------------------------------
// �O���t�B�b�N�X�̃C���X�^���X���擾
//---------------------------------------------------------
InputDevice* const InputDevice::GetInstance()
{
	if (m_InputDevice == nullptr)
	{
		m_InputDevice.reset(new InputDevice());
	}
	return m_InputDevice.get();
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
InputDevice::InputDevice()
	:
	m_keyboard{},             
	m_keyboardState{},        
	m_keyboardStateTracker{},
	m_mouse{},
	m_mouseState{},
	m_mouseButtonStateTracker{}
{
	
}

//---------------------------------------------------------
// ���\�[�X��ǂݍ���
// �V���O���g���C���X�^���X�̏���擾���̂݌Ăяo��
//---------------------------------------------------------
void InputDevice::CreateDevice()
{
	// �L�[�{�[�h�𐶐�����
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardState = std::make_unique<DirectX::Keyboard::State>();
    m_keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	// �}�E�X�𐶐�����
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouseState = std::make_unique<DirectX::Mouse::State>();
	m_mouseButtonStateTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void InputDevice::Update()
{
	// �L�[�{�[�h���X�V����
	UpdateKeyboardState();
	// �}�E�X���X�V����
	UpdateMouseState();
}

//---------------------------------------------------------
// �L�[�{�[�h���X�V����
//---------------------------------------------------------
void InputDevice::UpdateKeyboardState()
{
	*m_keyboardState = m_keyboard->GetState();
	m_keyboardStateTracker->Update(*m_keyboardState);
}

//---------------------------------------------------------
// �}�E�X���X�V����
//---------------------------------------------------------
void InputDevice::UpdateMouseState()
{
	*m_mouseState = m_mouse->GetState();
	m_mouseButtonStateTracker->Update(*m_mouseState);
}

