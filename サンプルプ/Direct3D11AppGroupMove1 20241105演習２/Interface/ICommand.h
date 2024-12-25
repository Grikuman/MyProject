#pragma once
#ifndef ICOMMAND_DEFINED
#define ICOMMAND_DEFINED
#include "Command/Header/Parameter.h"

// ICommandインターフェースを定義する
class ICommand
{
public:
	// コマンドID
	enum CommandID : int { MOVE, FLOAT, ROTATE, PLATE, SHOOT, UP, DOWN};

public:
	virtual CommandID GetCommandID() = 0;
	// パラメータを取得する
	virtual Parameter& GetParameter() = 0;
	// パラメータを設定する
	virtual void SetParameter(const Parameter& parameter) = 0;
	// 実行する
	virtual void Execute(Parameter& parameter, const float& t) = 0;
	// 仮想デストラクタ
	virtual ~ICommand() = default;
};

#endif	// ICOMMAND_DEFINED



