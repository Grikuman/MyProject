#pragma once
#ifndef FLOAT_COMMAND_DEFINED
#define FLOAT_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// 浮上コマンド
class FloatCommand : public ICommand
{
public:
	// コマンドIDを取得する
	CommandID GetCommandID() { return CommandID::FLOAT; }
	// パラメータを取得する
	Parameter& GetParameter() { return m_parameter; }
	// パラメータを設定する
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// コンストラクタ
	FloatCommand(const Parameter& parameter);
	// 線形補間を計算する
	DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t);
	// 浮上コマンドを実行する
	void Execute(Parameter& parameter, const float& t);

private:
	// パラメータ
	Parameter m_parameter;
};

#endif		// FLOAT_COMMAND_DEFINED
