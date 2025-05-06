/*
	�t�@�C�����FEventMessenger.h
	�@�@�@�T�v�F�C�x���g���Ǘ�����N���X
*/

#pragma once
#include "pch.h"
#include <unordered_map>
#include <functional>
#include "EventList.h"

class EventMessenger
{
public:
	// �C�x���g��o�^����
	static void Attach(const EventList event, std::function<void(void*)> function);
	// �Q�b�^�[��o�^
	static void AttachGetter(const GetterList event, std::function<void*()> function);
	// �C�x���g�����s����
	static void Execute(const EventList event, void* args);
	// �Q�b�^�[�����s����
	static void* ExecuteGetter(const GetterList event);
	// �C�x���g���폜����
	static void Detach(const EventList event);
	// �C�x���g���X�g���N���A����
	static void ClearEventList();

private:
	// �o�^���ꂽ�C�x���g��ۑ�����ϐ�
	static std::unordered_map<EventList, std::function<void(void*)>> m_eventList;
	static std::unordered_map<GetterList, std::function<void*()>> m_getterList;
};
