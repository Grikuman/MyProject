/*
	�t�@�C�����FEventMessenger.cpp
	�@�@�@�T�v�F�C�x���g���Ǘ�����N���X
*/
#include "pch.h"
#include "EventMessenger.h"

// �C�x���g���X�g�̏�����
std::unordered_map<EventList, std::function<void(void*)>> EventMessenger::m_eventList;
std::unordered_map<GetterList, std::function<void* ()>> EventMessenger::m_getterList;

// -------------------------------------------------
/// <summary>
/// �C�x���g��o�^����
/// </summary>
/// <param name="event">�C�x���g�̎��</param>
/// <param name="function">�o�^����֐�</param>
// -------------------------------------------------
void EventMessenger::Attach(const EventList event, std::function<void(void*)> function)
{
	// �C�x���g���X�g�ɐV�����C�x���g��o�^
	m_eventList[event] = function;
}

// -------------------------------------------------
/// <summary>
/// �Q�b�^�[�̈�x���g��o�^����
/// </summary>
/// <param name="event">�C�x���g�̎��</param>
/// <param name="function">�o�^����֐�</param>
// -------------------------------------------------
void EventMessenger::AttachGetter(const GetterList event, std::function<void* ()> function)
{
	// �C�x���g���X�g�ɐV�����C�x���g��o�^
	m_getterList[event] = function;
}

// -------------------------------------------------
/// <summary>
/// �C�x���g�����s����
/// </summary>
/// <param name="event">�C�x���g�̎��</param>
/// <param name="args">�C�x���g�̈���</param>
// -------------------------------------------------
void EventMessenger::Execute(const EventList event, void* args)
{
	// �C�x���g���X�g����̏ꍇ
	if (m_eventList.empty())
	{
		MessageBox(nullptr, L"�C�x���g��1���o�^����Ă��܂���", L"�G���[", MB_OK);
		return;
	}

	// �C�x���g���X�g����w�肳�ꂽ���O�̃C�x���g������
	auto foundEvent = m_eventList.find(event);

	if (foundEvent != m_eventList.end())
	{
		// void* �������Ƃ��Ċ֐����Ăяo��
		foundEvent->second(args);
	}
	else
	{
		// std::string �� std::wstring �ɕϊ�
		std::wstring wideEventName(L"���o�^�̃C�x���g");

		// MessageBox �ɓn��
		MessageBox(nullptr, wideEventName.c_str(), L"�G���[", MB_OK);
	}
}

// -------------------------------------------------
/// <summary>
/// �Q�b�^�[�����s����
/// </summary>
/// <param name="event">�C�x���g�̎��</param>
/// <returns>�C�x���g�̖߂�l</returns>
// -------------------------------------------------
void* EventMessenger::ExecuteGetter(const GetterList event)
{
	// �C�x���g������
	auto foundEvent = m_getterList.find(event);

	// �C�x���g��������������s
	if (foundEvent != m_getterList.end())
	{
		return foundEvent->second();
	}

	// �C�x���g��������Ȃ������ꍇ�A�G���[���b�Z�[�W��\��
	std::wstring wideEventName(L"���o�^�̃Q�b�^�[");

	// MessageBox �ɓn��
	MessageBox(nullptr, wideEventName.c_str(), L"�G���[", MB_OK);

	return nullptr;
}

// -------------------------------------------------
/// <summary>
/// �o�^���ꂽ�C�x���g����������
/// </summary>
/// <param name="event">��������C�x���g�̎��</param>
// -------------------------------------------------
void EventMessenger::Detach(const EventList event)
{
	if (m_eventList.empty()) {
		MessageBox(nullptr, L"�C�x���g��1�����݂��܂���", L"�G���[", MB_OK);
		return;
	}

	m_eventList.erase(event);
}

// -------------------------------------------------
/// <summary>
/// �C�x���g���X�g���k�ɂ���
/// </summary>
// -------------------------------------------------
void EventMessenger::ClearEventList()
{
	// �ʏ�C�x���g���N���A
	m_eventList.clear();
	// �Q�b�^�[�C�x���g���N���A
	m_getterList.clear();
}