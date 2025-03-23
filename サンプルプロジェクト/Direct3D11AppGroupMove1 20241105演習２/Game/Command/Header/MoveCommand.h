#pragma once
#ifndef MOVE_COMMAND_DEFINED
#define MOVE_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// 移動コマンド
class MoveCommand : public ICommand
{
public:
	// コマンドIDを取得する
	CommandID GetCommandID() { return CommandID::MOVE; }
	// パラメータを取得する
	Parameter& GetParameter() { return m_parameter; }
	// パラメータを設定する
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// コンストラクタ
	MoveCommand(const Parameter& parameter);
	// 線形補間を計算する
	DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t);
	// 移動コマンドを実行する
	void Execute(Parameter& parameter, const float& t);

private:
	// パラメータ
	Parameter m_parameter;
};

#endif		// MOVE_COMMAND_DEFINED
