#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED
#include <unordered_map>
#include "IComponent.h"
#include "ISubject.h"
#include "Turret/Header/Turret.h"

// Subject�N���X���`����
class Messenger : public ISubject
{
public:
	// �R�}���h���s���擾����
	static bool GetCommandExecution();
	// �R�}���h���s��ݒ肷��
	static void SetCommandExecution(bool commandExecution);

	// �ώ@�҂��A�^�b�`����
	static void Attach(const DirectX::Keyboard::Keys& keys, IComponent* observer);
	// �ώ@�҂��f�^�b�`����
	static void Detach(const DirectX::Keyboard::Keys& keys, IComponent* component);
	// �L�[���͂ɂ��ώ@�҂ɒʒm����
	static void Notify(const DirectX::Keyboard::State& keyboardState, const std::vector<int>& playerNodeNumbers);
	static void Notify(const DirectX::Keyboard::Keys& keys, const std::vector<int>& playerNodeNumbers);
	static void Notify(const DirectX::Keyboard::Keys& keys);
	// ���{�^�����N���b�N���ꂽ���Ƀv���C���[�ώ@�҂ɒʒm����
	static void NotifyToPlayer(const DirectX::SimpleMath::Vector3& mousePosition);
// �ώ@�҃��X�g���\�[�g����
	static void SortObserverList();
	//  �L�[�͈̓��X�g�𐶐�����
	static void CreateKeyRangeList();

private:
	// �R�}���h���s��
	static bool m_commandExecution;
	// �L�[�{�[�h�ώ@�҃��X�g
	static std::vector<std::pair<DirectX::Keyboard::Keys, IComponent*>> s_observerList;
	// �L�[�͈̓��X�g(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)
	static std::unordered_map<DirectX::Keyboard::Keys, std::pair<size_t, size_t>> s_keysRangeList;
};

#endif	// MESSENGER_DEFINED