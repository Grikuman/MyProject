#include "Framework/pch.h"
#include "Observer/Messenger.h"
#include "Team/Team.h"
#include "Interface/IObserver.h"
#include "Turret/Header/Turret.h"

// �R�}���h���s��
bool Messenger::m_commandExecution = false;
// �L�[�{�[�h�ώ@�҃��X�g������������
std::vector<std::pair<DirectX::Keyboard::Keys, IComponent*>> Messenger::s_observerList;
// �L�[�͈̓��X�g(�L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X))
std::unordered_map<DirectX::Keyboard::Keys, std::pair<size_t, size_t>> Messenger::s_keysRangeList;

// �R�}���h���s���擾����
bool Messenger::GetCommandExecution() { return m_commandExecution; }
// �R�}���h���s��ݒ肷��
void Messenger::SetCommandExecution(bool commandExecution) { m_commandExecution = commandExecution; }


// �ώ@�҂��A�^�b�`����
void Messenger::Attach(const DirectX::Keyboard::Keys& keys, IComponent* observer)
{
	// �ώ@�҃��X�g�Ɋώ@�҂�ǉ�����
	s_observerList.emplace_back(std::make_pair(keys, observer));
}

// �ώ@�҂��f�^�b�`����
void Messenger::Detach(const DirectX::Keyboard::Keys& keys, IComponent* observer)
{
	// �ώ@�҃��X�g����ώ@�҂���������
	s_observerList.erase
	(
		std::remove_if(s_observerList.begin(), s_observerList.end(),
			[&keys, observer](const std::pair<DirectX::Keyboard::Keys, IComponent*>& entry) 
			{
				return entry.first == keys && entry.second == observer;
			}),
		s_observerList.end()
	);
}

// �ώ@�҂ɒʒm����
void Messenger::Notify(const DirectX::Keyboard::State& keyboardState, const std::vector<int>& playerNodeNumbers)
{
	// �u�ώ@�҃��X�g�v����L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)�����o��
	for (const auto& keyRange : s_keysRangeList)
	{
		// �ώ@�҂��������ׂ��L�[���ǂ����𒲂ׂ�
		if (keyboardState.IsKeyDown(keyRange.first))
		{
			// �L�[�̊J�n�C���f�b�N�X����I���C���f�b�N�X�܂ł̃C���f�b�N�X���o��
			for (auto range = keyRange.second.first; range <= keyRange.second.second; range++)
			{
				// �v���C���[�m�[�h�ԍ��z�񂩂�v���C���[�m�[�h�ԍ������o��
				for (const auto& playerNodeNumber : playerNodeNumbers)
				{
					// �v���C���[�m�[�h�ԍ��Ɗώ@�҂̃m�[�h�ԍ����������ꍇ �ώ@�҂ɃL�[��ʒm����
					if (playerNodeNumber == s_observerList[range].second->GetNodeNumber())
					{
						// �ώ@�҂̒ʒm�֐��ɉ�������ꂽ�L�[��ʒm����
						s_observerList[range].second->OnKeyPressed(s_observerList[range].first);
					}
				}
			}
		}
	}
}

// �L�[���͂ɂ��ώ@�҂ɒʒm����
void Messenger::Notify(const DirectX::Keyboard::Keys& keys, const std::vector<int>& playerNodeNumbers)
{
	// �u�ώ@�҃��X�g�v����L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)�����o��
	auto it = s_keysRangeList.find(keys);

	// �L�[�̊J�n�C���f�b�N�X����I���C���f�b�N�X�܂ł̃C���f�b�N�X���o��
	for (auto range = it->second.first; range <= it->second.second; range++)
	{
		// �v���C���[�m�[�h�ԍ��z�񂩂�v���C���[�m�[�h�ԍ������o��
		for (const auto& playerNodeNumber : playerNodeNumbers)
		{
			// �v���C���[�m�[�h�ԍ��Ɗώ@�҂̃m�[�h�ԍ����������ꍇ �ώ@�҂ɃL�[��ʒm����
			if (playerNodeNumber == s_observerList[range].second->GetNodeNumber())
			{
				// �ώ@�҂̒ʒm�֐��ɉ�������ꂽ�L�[��ʒm����
				s_observerList[range].second->OnKeyPressed(s_observerList[range].first);
			}
		}
	}
}

// �L�[���͂ɂ��ώ@�҂ɒʒm����
void Messenger::Notify(const DirectX::Keyboard::Keys& keys)
{
	// �u�ώ@�҃��X�g�v����L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)�����o��
	auto it = s_keysRangeList.find(keys);

	// �L�[�̊J�n�C���f�b�N�X����I���C���f�b�N�X�܂ł̃C���f�b�N�X���o��
	for (auto range = it->second.first; range <= it->second.second; range++)
	{
		// �ώ@�҂̒ʒm�֐��ɉ�������ꂽ�L�[��ʒm����
		s_observerList[range].second->OnKeyPressed(keys);
	}
}

// ���{�^�����N���b�N���ꂽ���Ƀv���C���[�̊ώ@�҂ɒʒm����
void Messenger::NotifyToPlayer(const DirectX::SimpleMath::Vector3& mousePosition)
{
	// �v���C���[�`�[���ԍ����擾����
	int playerTeamNumber = Team::GetPlayerTeamNumber();
	// �v���C���[�m�[�h�ԍ��z����擾����
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);
	for (auto& nodeNumber : playerNodeNumbers)
	{
		// �v���C���[�C�����擾����
		Turret* turret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber));
		// ���{�^�����N���b�N���ꂽ���Ƀv���C���[�ώ@�҂ɒʒm����
		turret->OnLeftButtonClicked(mousePosition);
	}
}

// �u�ώ@�҃��X�g�v���\�[�g����
void Messenger::SortObserverList()
{
	// �u�ώ@�҃��X�g�v���L�[�Ń\�[�g����
	std::sort(
		s_observerList.begin(), 
		s_observerList.end(),
		[](const std::pair<DirectX::Keyboard::Keys, IComponent*>& a, const std::pair<DirectX::Keyboard::Keys, IComponent*>& b)
		{
			return a.first < b.first;
		});
}

//  �L�[�͈̓��X�g�𐶐�����
void Messenger::CreateKeyRangeList()
{
	// �J�n�C���f�b�N�X��ݒ肷��
	size_t  startIndex = 0;
	// �u�L�[�͈̓��X�g�v�Ńf�[�^�����݂���ꍇ�́u�L�[�͈̓��X�g�v���N���A����
	if (s_keysRangeList.size()) 
		s_keysRangeList.clear();
	// �u�ώ@�҃��X�g�v�̊J�n�L�[�����݂̃L�[�ɂ���
	DirectX::Keyboard::Keys currentKey = s_observerList[startIndex].first;
	// �u�ώ@�҃��X�g�v�̊J�n����I���܂ŌJ��Ԃ�
	for (size_t  index = 1; index < s_observerList.size(); index++) 
	{
		// �u�ώ@�҃��X�g�v�̃L�[�ƌ��݂̃L�[���������Ȃ��Ȃ����ꍇ
		if (s_observerList[index].first != currentKey) 
		{
			// �L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)���u�L�[�͈̓��X�g�v�ɒǉ�����
			s_keysRangeList.emplace(currentKey, std::make_pair(startIndex, index - 1));
			// �C���f�b�N�X���J�n�C���f�b�N�X�ɐݒ肷��
			startIndex = index;
			// �u�ώ@�҃��X�g�v�̃L�[�����݂̃L�[�ɐݒ肷��
			currentKey = s_observerList[index].first;
		}
	}
	// �L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)���u�L�[�͈̓��X�g�v�ɒǉ�����
	s_keysRangeList.emplace(currentKey, std::make_pair(startIndex, s_observerList.size() - 1));
}
