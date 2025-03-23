#pragma once
#pragma once
#ifndef PLATE_COMMAND_DEFINED
#define PLATE_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// プレートを開閉する
class PlateCommand : public ICommand
{
	enum State : int { MOVE, STOP };

public:
	// コマンドIDを取得する
	CommandID GetCommandID() { return CommandID::PLATE; }
	// パラメータを取得する
	Parameter& GetParameter() { return m_parameter; }
	// パラメータを設定する
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// コンストラクタ
	PlateCommand(const Parameter& parameter);
	// 線形補間を計算する
	DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t);
	// 移動コマンドを実行する
	void Execute(Parameter& parameter, const float& t);

private:
	// パラメータ
	Parameter m_parameter;
};

#endif		// PLATE_COMMAND_DEFINED
