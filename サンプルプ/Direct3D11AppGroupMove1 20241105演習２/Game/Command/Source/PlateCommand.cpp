#include "Framework/pch.h"
#include "Command/Header/PlateCommand.h"
#include "Team/Team.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretPlate.h"
#include "Observer/Messenger.h"

// �R���X�g���N�^
PlateCommand::PlateCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// ���`��Ԃ��v�Z����
DirectX::SimpleMath::Vector3 PlateCommand::Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// �v���[�g�R�}���h�����s����
void PlateCommand::Execute(Parameter& parameter, const float& t)
{
	UNREFERENCED_PARAMETER(parameter);
	UNREFERENCED_PARAMETER(t);

	// �v���C���[�`�[���ԍ����擾����
	int playerTeamNumber = Team::GetPlayerTeamNumber();
	// �v���C���[�`�[���̃m�[�h�ԍ��z����擾����
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);
	// �C���v���[�g�ɒʒm����
	Messenger::Notify(DirectX::Keyboard::Keys::P, playerNodeNumbers);
}
