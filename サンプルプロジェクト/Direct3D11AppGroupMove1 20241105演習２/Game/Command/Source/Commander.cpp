#include "Framework/pch.h"
#include "Command/Header/Commander.h"
#include "Observer/Messenger.h"

// コンストラクタ
Commander::Commander()
	:
	m_command(nullptr),								// コマンド
	m_parameter{},											// パラメータ
	m_t(0.0f),														// 補間比率
	m_macroCommand{},								// マクロコマンド
	m_macroParameter{},								// マクロパラメータ
	m_commandIndex(0)								// コマンドインデックス
{
}

// デストラクタ
Commander::~Commander()
{
}

// 初期化する
void Commander::Initialize()
{
	using namespace DirectX::SimpleMath;

}

// マクロコマンドをクリアする
void Commander::ClearCommand()
{
	// マクロコマンドをクリアする
	m_macroCommand.clear();
}

// マクロコマンドにコマンドを追加する
void Commander::AddCommand(std::unique_ptr<ICommand> command)
{
	// マクロコマンドにコマンドを追加する
	m_macroCommand.emplace_back(std::move(command));
}

// マクロコマンドを実行する
bool Commander::ExecuteMacroCommand(DirectX::SimpleMath::Vector3& position, DirectX::SimpleMath::Quaternion& angle)
{
	Parameter& parameter = m_macroCommand[m_commandIndex]->GetParameter();
	// コマンド実行開始する
	Messenger::SetCommandExecution(true);

	if (m_t == 0.0f)
	{
		// コマンドの初期値を設定する
		if (m_commandIndex == 0)
		{
			// 開始位置を設定する
			parameter.SetStartPosition(position);
			// 終了位置を設定する
			parameter.CalculateEndPositionH(position, angle);
			// 水平開始回転角を設定する
			parameter.SetStartAngle(angle);
			// 水平終了回転角を設定する
			parameter.SetEndAngle(angle * parameter.GetAngle());

			switch (m_macroCommand[m_commandIndex]->GetCommandID())
			{
			case ICommand::CommandID::FLOAT:
				// 垂直終了位置を設定する
				parameter.CalculateEndPositionV(position, angle);
				break;
			}
		}
		else
		{
			// 開始位置を設定する
			parameter.SetStartPosition(m_macroCommand[m_commandIndex - 1]->GetParameter().GetEndPosition());
			// 水平終了位置を設定する
			parameter.CalculateEndPositionH(parameter.GetStartPosition(), angle);
			// 開始回転角を設定する
			parameter.SetStartAngle(m_macroCommand[m_commandIndex - 1]->GetParameter().GetEndAngle());
			// 水平終了回転角を設定する
			parameter.SetEndAngle(parameter.GetStartAngle() * parameter.GetAngle());

			switch (m_macroCommand[m_commandIndex]->GetCommandID())
			{
			case ICommand::CommandID::FLOAT:
				// 垂直終了位置を設定する
				parameter.CalculateEndPositionV(parameter.GetStartPosition(), parameter.GetAngle());
				break;
			}
		}
	}

	if (m_t < 1.0f)
	{
		// 線形補間係数によりコマンドを実行する
		m_macroCommand[m_commandIndex]->Execute(parameter, m_t);

		switch (m_macroCommand[m_commandIndex]->GetCommandID())
		{
		case ICommand::CommandID::PLATE:
		case ICommand::CommandID::UP:
		case  ICommand::CommandID::DOWN:
			// 一度だけ実行する
			m_t = 1.0f;
			break;

		case  ICommand::CommandID::ROTATE:
		case ICommand::CommandID::SHOOT:
			// 線形補間により現在の回転角を更新する
			angle = m_macroCommand[m_commandIndex]->GetParameter().GetCurrentAngle();
			break;

		case  ICommand::CommandID::MOVE:
		case ICommand::CommandID::FLOAT:
			// 線形補間により現在の位置を更新する
			position = m_macroCommand[m_commandIndex]->GetParameter().GetCurrentPosition();
			break;
		}
		// 補間比率を加算する
		m_t += 0.005f;
	}
	else
	{
		// 次のコマンドのため補間比率をリセットする
		m_t = 0.0f;
		// 次のコマンドのためコマンドインデックスをインクリメントする
		m_commandIndex++;
	}
	// マクロインデックスがマクロコマンド数と同じになったらマクロコマンドを終了する
	if (m_commandIndex == m_macroCommand.size())
	{
		// マクロコマンドインデックスをリセットする
		m_commandIndex = 0;
		// コマンド実行を終了する
		Messenger::SetCommandExecution(false);
		// コマンダーを終了する
		return false;
	}
	return true;
}
