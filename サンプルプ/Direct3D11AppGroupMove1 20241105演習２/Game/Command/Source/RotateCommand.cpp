#include "Framework/pch.h"
#include "Command/Header/RotateCommand.h"

// コンストラクタ
RotateCommand::RotateCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// 回転コマンドを実行する
void RotateCommand::Execute(Parameter& parameter, const float& t)
{
	// クォータニオンの線形補間を行う
	parameter.SetCurrentAngle(DirectX::SimpleMath::Quaternion::Lerp(parameter.GetStartAngle(), parameter.GetEndAngle(), t));
	// パラメータを更新する
	m_parameter = parameter;
}