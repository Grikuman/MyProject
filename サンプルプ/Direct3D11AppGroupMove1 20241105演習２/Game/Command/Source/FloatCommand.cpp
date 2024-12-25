#include "Framework/pch.h"
#include "Command/Header/FloatCommand.h"

// コンストラクタ
FloatCommand::FloatCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// 線形補間を計算する
DirectX::SimpleMath::Vector3 FloatCommand::Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// 浮上コマンドを実行する
void FloatCommand::Execute(Parameter& parameter, const float& t)
{
	// 線形補間で浮上中の現在位置を計算する
	parameter.SetCurrentPosition(Lerp(parameter.GetStartPosition(), parameter.GetEndPosition(), t));
	// パラメータを更新する
	m_parameter = parameter;
}