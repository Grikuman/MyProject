#pragma once
#ifndef ROTETE_COMMAND_DEFINED
#define ROTETE_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// 回転コマンド
class RotateCommand : public ICommand
{
public:
	// コマンドIDを取得する
	CommandID GetCommandID() { return CommandID::ROTATE; }
	// パラメータを取得する
	Parameter& GetParameter() { return m_parameter; }
	// パラメータを設定する
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// コンストラクタ
	RotateCommand(const Parameter& parameter);
	// 回転コマンドを実行する
	void Execute(Parameter& parameter, const float& t);

private:
	// パラメータ
	Parameter m_parameter;
};

#endif		// ROTATE_COMMAND_DEFINED