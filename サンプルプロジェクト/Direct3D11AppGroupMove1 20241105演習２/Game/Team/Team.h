#pragma once
#include <unordered_map>
#include <vector>
#include <mutex>
#include "Interface/IComponent.h"
#include "Turret/Header/Turret.h"

#ifndef TEAM_DEFINED
#define TEAM_DEFINED

class Team
{
	// �G���v�e�B
	static const std::vector<int> EMPTY_LIST;

public:
	// �v���C���[�`�[���ԍ����擾����
	static int GetPlayerTeamNumber() { return s_playerTeamNumber; }
	// �v���C���[�`�[���ԍ���ݒ肷��
	static void SetPlayerTeamNumber(int teamNumber) { s_playerTeamNumber = teamNumber; }
	// �G�l�~�[�`�[���ԍ����擾����
	static int GetEnemyTeamNumber() { return s_enemyTeamNumber; }
	// �G�l�~�[�`�[���ԍ���ݒ肷��
	static void SetEnemyTeamNumber(int teamNumber) { s_enemyTeamNumber = teamNumber; }
	// �w�肳�ꂽ�`�[���ԍ��ƓG�΂���`�[���ԍ����擾����
	static int GetOpposingTeamNumber(int teamNumber) { return (teamNumber == s_playerTeamNumber) ? s_enemyTeamNumber : s_playerTeamNumber; }
	// �`�[���ԍ�����m�[�h���X�g���擾����
	static const std::vector<int>& GetNodeListForTeam(int teamNumber);
	// �m�[�h�ԍ�����`�[���ԍ����擾����
	static int GetTeamNumberForNodeNumber(int nodeNumber);
	// �m�[�h�ԍ�����C���Q�ƃ��X�g�̃m�[�h���擾����
	static IComponent* GetNodeFromTurretReferenceList(int nodeNumber);
	// �v���C���[�`�[�����S�ʒu���擾����
	static DirectX::SimpleMath::Vector3& GetPlayerTeamCenterPosition();
	// �G�`�[�����S�ʒu���擾����
	static DirectX::SimpleMath::Vector3& GetEnemyTeamCenterPosition();
	// �v���C���[�ƓG���X�C�b�`�������ǂ������擾����
	static bool GetOpponentSwitch() { return s_opponentSwitch; }

public:
	// �Q�ƃ��X�g�Ƀm�[�h��ǉ�����
	static void AddNodeToReferenceList(int nodeNumber, IComponent* node);
	// �v���C���[�`�[����ύX����
	static void ChangePlayerTeam();
	// �C���Q�ƃ��X�g����m�[�h���폜����
	static void DeleteNodeFromTurretReferenceList(int nodeNumber);

private:
	// �v���C���[�`�[���ԍ�
	static int s_playerTeamNumber;
	// �G�l�~�[�`�[���ԍ�
	static int s_enemyTeamNumber;
	// �`�[�����X�g(�`�[���ԍ��ƃm�[�h�ԍ��z��)
	static std::unordered_map<int, std::vector<int>> s_teamList;
	// �C���Q�ƃ��X�g
	static std::unordered_map<int, IComponent* > s_nodeReferenceList;
	// �v���C���[�`�[�������ʒu
	static DirectX::SimpleMath::Vector3 s_playerTeamCenterPosition;
	// �G�`�[�������ʒu
	static DirectX::SimpleMath::Vector3 s_enemyTeamCenterPosition;
	// �~���[�e�b�N�X
	static std::mutex m_mutex;
	// �v���C���[�ƓG���X�C�b�`�������ǂ���
	static bool s_opponentSwitch;
};

#endif		// TEAM_DEFINED
