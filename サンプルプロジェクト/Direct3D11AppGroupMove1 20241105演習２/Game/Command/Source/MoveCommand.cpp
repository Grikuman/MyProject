#include "Framework/pch.h"
#include "Command/Header/MoveCommand.h"

// コンストラクタ
MoveCommand::MoveCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// 線形補間を計算する
DirectX::SimpleMath::Vector3 MoveCommand::Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// 移動コマンドを実行する
void MoveCommand::Execute(Parameter& parameter, const float& t)
{
	// 線形補間で移動中の現在位置を計算する
	parameter.SetCurrentPosition(Lerp(parameter.GetStartPosition(), parameter.GetEndPosition(), t));
	// パラメータを更新する
	m_parameter = parameter;
}
