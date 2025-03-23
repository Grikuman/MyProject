#include "Framework/pch.h"
#include "Command/Header/PlateCommand.h"
#include "Team/Team.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretPlate.h"
#include "Observer/Messenger.h"

// コンストラクタ
PlateCommand::PlateCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// 線形補間を計算する
DirectX::SimpleMath::Vector3 PlateCommand::Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// プレートコマンドを実行する
void PlateCommand::Execute(Parameter& parameter, const float& t)
{
	UNREFERENCED_PARAMETER(parameter);
	UNREFERENCED_PARAMETER(t);

	// プレイヤーチーム番号を取得する
	int playerTeamNumber = Team::GetPlayerTeamNumber();
	// プレイヤーチームのノード番号配列を取得する
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);
	// 砲塔プレートに通知する
	Messenger::Notify(DirectX::Keyboard::Keys::P, playerNodeNumbers);
}
