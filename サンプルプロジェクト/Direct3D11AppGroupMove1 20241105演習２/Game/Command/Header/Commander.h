#pragma once
#ifndef COMMANDER_DEFINED
#define COMMANDER_DEFINED
#include "ICommand.h"

// Commanderクラスを定義する
class Commander
{
public:
	// コマンドを取得する
	ICommand* GetCommand() { return m_command; }
	// コマンドを設定する
	void SetCommand(ICommand* command) { m_command = command; }
	// パラメータを取得する
	Parameter GetParameter() { return m_parameter; }
	// パラメータを設定する
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

	// マクロコマンド数を取得する
	size_t GetMacroCommandNumber() { return m_macroCommand.size(); }

public:
	// コンストラクタ
	Commander();
	// デストラクタ
	~Commander();
	// 初期化する
	void Initialize();
	// マクロコマンドをクリアする
	void ClearCommand();
	// マクロコマンドにコマンドを追加する
	void AddCommand(std::unique_ptr<ICommand> command);
	// マクロコマンドを実行する
	bool ExecuteMacroCommand(DirectX::SimpleMath::Vector3& position, DirectX::SimpleMath::Quaternion& angle);
	// 線形補間をリセットする
	void ResetLerp() { m_t = 0.0f; }

private:
	// コマンド
	ICommand* m_command;
	// マクロコマンド配列
	std::vector<std::unique_ptr<ICommand>> m_macroCommand;
	// パラメータ
	Parameter m_parameter;
	// マクロパラメータ配列
	std::vector<Parameter> m_macroParameter;
	// 補間比率
	float m_t;
	// コマンドインデックス
	int m_commandIndex;
};

#endif		// COMMANDER_DEFINED

