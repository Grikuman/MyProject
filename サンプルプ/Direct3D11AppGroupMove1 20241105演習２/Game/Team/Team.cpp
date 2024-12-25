#include "Framework/pch.h"
#include "Game/Team/Team.h"

// �~���[�e�b�N�X������������ 
std::mutex Team::m_mutex{};
// �v���C���[�`�[���ԍ��̏�����
int Team::s_playerTeamNumber = 0;
// �G�l�~�[�`�[���ԍ��̏�����
int Team::s_enemyTeamNumber = 1;
// �v���C���[�`�[�����S�ʒu
DirectX::SimpleMath::Vector3 Team::s_playerTeamCenterPosition = DirectX::SimpleMath::Vector3::Zero;
// �G�l�~�[�`�[�����S�ʒu
DirectX::SimpleMath::Vector3 Team::s_enemyTeamCenterPosition = DirectX::SimpleMath::Vector3::Zero;
// �v���C���[�ƓG���X�C�b�`�������ǂ���
bool Team::s_opponentSwitch = false;

// �`�[�����X�g(�`�[���ԍ��ƃm�[�h�ԍ��z��)�̏�����
std::unordered_map<int, std::vector<int>> Team::s_teamList =
{
	{0,	{ 1,  2,   3,   4,  5}},							// �O���[�v 0 : {  1,   2,   3,   4,   5}
	{1,	{ 6,  7,   8,   9,  10,  11,  12}},		// �O���[�v 1 : {  6,   7,   8,   9,   10,  11,  12} 
};

// �Q�ƃ��X�g�̏�����
std::unordered_map<int, IComponent* > Team::s_nodeReferenceList = {};
// �󃊃X�g
const std::vector<int> Team::EMPTY_LIST = {};

// �`�[���ԍ�����m�[�h���X�g���擾����
const std::vector<int>& Team::GetNodeListForTeam(int teamNumber)
{
	// �`�[���ԍ�����m�[�h���X�g��T��
	auto it = s_teamList.find(teamNumber);
	// �m�[�h���X�g�����o�����ꍇ�m�[�h���X�g�z���Ԃ�
	if (it != s_teamList.end())
	{
		// �m�[�h���X�g�̔z���Ԃ�
		return it->second;
	}
	// �m�[�h���X�g��������Ȃ��ꍇ�͋�̔z���Ԃ�
	return EMPTY_LIST;
}

// �m�[�h�ԍ�����`�[���ԍ����擾����
int Team::GetTeamNumberForNodeNumber(int nodeNumber)
{
	for (auto& team : s_teamList)
	{
		// �m�[�h���X�g�z����擾����
		std::vector<int>& nodeArray = team.second;
		// �m�[�h���X�g�z��̃m�[�h��I������
		for (int node : nodeArray)
		{
			// �m�[�h���X�g�z��̔ԍ��ƃm�[�h�ԍ����������ꍇ�Ƀ`�[���ԍ���Ԃ�
			if (node == nodeNumber)
			{
				// �`�[���ԍ���Ԃ�
				return team.first;
			}
		}
	}
	// �ǂ̃`�[���ɂ������Ă��Ȃ��ꍇ�� -1 ��Ԃ�
	return -1;
}

// �Q�ƃ��X�g�Ƀm�[�h��ǉ�����
void Team::AddNodeToReferenceList(int nodeNumber, IComponent* node)
{
	// �m�[�h�ԍ��ƃm�[�h��}������
	s_nodeReferenceList.insert({ nodeNumber, node });
}

// �m�[�h�ԍ�����C���Q�ƃ��X�g�̃m�[�h���擾����
IComponent* Team::GetNodeFromTurretReferenceList(int nodeNumber)
{
	// �m�[�h�ԍ�����m�[�h����������
	auto it = s_nodeReferenceList.find(nodeNumber);
	// �m�[�h�����������ꍇ�Ƀm�[�h��Ԃ�
	if (it != s_nodeReferenceList.end())
		return it->second;
	else
		return nullptr;
}

// �v���C���[�`�[����ύX����
void Team::ChangePlayerTeam()
{
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();
	// �����z����쐬����
	std::vector<bool> digital = { keyboardState.D0, keyboardState.D1 };
	// �ǂ̐����������������𒲂ׂ�
	for (int index = 0; index < digital.size(); index++)
	{
		// ��������ꂽ�������v���C���[�`�[���ԍ��ɂȂ�
		if (digital[index])
		{
			if (index == s_enemyTeamNumber) 
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				// �G�l�~�[�`�[���ԍ����擾����
				int enemyTeamNumber = s_playerTeamNumber;
				// �v���C���[�`�[���ԍ����擾����
				int playerTeamNumber = index;
				// �v���C���[�`�[���ԍ���ݒ肷��
				s_playerTeamNumber = playerTeamNumber;
				// �G�l�~�[�`�[���ԍ���ݒ肷��
				s_enemyTeamNumber = enemyTeamNumber;
				// �v���C���[�ƓG���؂�ւ����
				s_opponentSwitch = (s_opponentSwitch == false) ? true : false;
			}
		}
	}
}

// �C���Q�ƃ��X�g����m�[�h���폜����
void Team::DeleteNodeFromTurretReferenceList(int nodeNumber)
{
	// �m�[�h�ԍ������t�@�����X���X�g����T��
	auto it = s_nodeReferenceList.find(nodeNumber);
	// �m�[�h�ԍ������t�@�����X���X�g�ɑ��݂���ꍇ�m�[�h���폜����
	if (it != s_nodeReferenceList.end())
	{
		// �m�[�h���폜����
		s_nodeReferenceList.erase(it);
	}
}

// �v���C���[�`�[�����S�ʒu���擾����
DirectX::SimpleMath::Vector3& Team::GetPlayerTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// �v���C���[�`�[���ԍ����擾����
	int playerTeamNumber = GetPlayerTeamNumber();
	// �v���C���[�m�[�h�ԍ��z����擾����
	std::vector<int> playerNodeNumbers = GetNodeListForTeam(playerTeamNumber);
	// �ʒu�W�v���N���A����
	Vector3 sumPosition(Vector3::Zero);
	for (auto& nodeNumber : playerNodeNumbers)
	{
		// �v���C���[�C�����擾����
		Turret* turret = dynamic_cast<Turret*>(GetNodeFromTurretReferenceList(nodeNumber));
		// �ʒu���v���v�Z����
		sumPosition = sumPosition + turret->GetPosition();
	}
	// �v���C���[�`�[���̒����ʒu���v�Z����
	s_playerTeamCenterPosition = sumPosition / (float)playerNodeNumbers.size();
	// �v���C���[�`�[�����S�ʒu��Ԃ�
	return s_playerTeamCenterPosition;
}

// �G�l�~�[�`�[�����S�ʒu���擾����
DirectX::SimpleMath::Vector3& Team::GetEnemyTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// �G�l�~�[�`�[���ԍ����擾����
	int enemyTeamNumber = GetEnemyTeamNumber();
	// �G�l�~�[�m�[�h�ԍ��z����擾����
	std::vector<int> enemyNodeNumbers = GetNodeListForTeam(enemyTeamNumber);
	// �ʒu�W�v���N���A����
	Vector3 sumPosition(Vector3::Zero);
	for (auto& nodeNumber : enemyNodeNumbers)
	{
		// �G�l�~�[�C�����擾����
		Turret* turret = dynamic_cast<Turret*>(GetNodeFromTurretReferenceList(nodeNumber));
		// �ʒu���v���v�Z����
		sumPosition = sumPosition + turret->GetPosition();
	}
	// �G�l�~�[�`�[���̒����ʒu���v�Z����
	s_enemyTeamCenterPosition = sumPosition / (float)enemyNodeNumbers.size();
	// �G�l�~�[�`�[�����S�ʒu��Ԃ�
	return s_enemyTeamCenterPosition;
}