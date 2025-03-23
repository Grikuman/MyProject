#include "Framework/pch.h"
#include "Command/Header/Commander.h"
#include "Observer/Messenger.h"

// �R���X�g���N�^
Commander::Commander()
	:
	m_command(nullptr),								// �R�}���h
	m_parameter{},											// �p�����[�^
	m_t(0.0f),														// ��Ԕ䗦
	m_macroCommand{},								// �}�N���R�}���h
	m_macroParameter{},								// �}�N���p�����[�^
	m_commandIndex(0)								// �R�}���h�C���f�b�N�X
{
}

// �f�X�g���N�^
Commander::~Commander()
{
}

// ����������
void Commander::Initialize()
{
	using namespace DirectX::SimpleMath;

}

// �}�N���R�}���h���N���A����
void Commander::ClearCommand()
{
	// �}�N���R�}���h���N���A����
	m_macroCommand.clear();
}

// �}�N���R�}���h�ɃR�}���h��ǉ�����
void Commander::AddCommand(std::unique_ptr<ICommand> command)
{
	// �}�N���R�}���h�ɃR�}���h��ǉ�����
	m_macroCommand.emplace_back(std::move(command));
}

// �}�N���R�}���h�����s����
bool Commander::ExecuteMacroCommand(DirectX::SimpleMath::Vector3& position, DirectX::SimpleMath::Quaternion& angle)
{
	Parameter& parameter = m_macroCommand[m_commandIndex]->GetParameter();
	// �R�}���h���s�J�n����
	Messenger::SetCommandExecution(true);

	if (m_t == 0.0f)
	{
		// �R�}���h�̏����l��ݒ肷��
		if (m_commandIndex == 0)
		{
			// �J�n�ʒu��ݒ肷��
			parameter.SetStartPosition(position);
			// �I���ʒu��ݒ肷��
			parameter.CalculateEndPositionH(position, angle);
			// �����J�n��]�p��ݒ肷��
			parameter.SetStartAngle(angle);
			// �����I����]�p��ݒ肷��
			parameter.SetEndAngle(angle * parameter.GetAngle());

			switch (m_macroCommand[m_commandIndex]->GetCommandID())
			{
			case ICommand::CommandID::FLOAT:
				// �����I���ʒu��ݒ肷��
				parameter.CalculateEndPositionV(position, angle);
				break;
			}
		}
		else
		{
			// �J�n�ʒu��ݒ肷��
			parameter.SetStartPosition(m_macroCommand[m_commandIndex - 1]->GetParameter().GetEndPosition());
			// �����I���ʒu��ݒ肷��
			parameter.CalculateEndPositionH(parameter.GetStartPosition(), angle);
			// �J�n��]�p��ݒ肷��
			parameter.SetStartAngle(m_macroCommand[m_commandIndex - 1]->GetParameter().GetEndAngle());
			// �����I����]�p��ݒ肷��
			parameter.SetEndAngle(parameter.GetStartAngle() * parameter.GetAngle());

			switch (m_macroCommand[m_commandIndex]->GetCommandID())
			{
			case ICommand::CommandID::FLOAT:
				// �����I���ʒu��ݒ肷��
				parameter.CalculateEndPositionV(parameter.GetStartPosition(), parameter.GetAngle());
				break;
			}
		}
	}

	if (m_t < 1.0f)
	{
		// ���`��ԌW���ɂ��R�}���h�����s����
		m_macroCommand[m_commandIndex]->Execute(parameter, m_t);

		switch (m_macroCommand[m_commandIndex]->GetCommandID())
		{
		case ICommand::CommandID::PLATE:
		case ICommand::CommandID::UP:
		case  ICommand::CommandID::DOWN:
			// ��x�������s����
			m_t = 1.0f;
			break;

		case  ICommand::CommandID::ROTATE:
		case ICommand::CommandID::SHOOT:
			// ���`��Ԃɂ�茻�݂̉�]�p���X�V����
			angle = m_macroCommand[m_commandIndex]->GetParameter().GetCurrentAngle();
			break;

		case  ICommand::CommandID::MOVE:
		case ICommand::CommandID::FLOAT:
			// ���`��Ԃɂ�茻�݂̈ʒu���X�V����
			position = m_macroCommand[m_commandIndex]->GetParameter().GetCurrentPosition();
			break;
		}
		// ��Ԕ䗦�����Z����
		m_t += 0.005f;
	}
	else
	{
		// ���̃R�}���h�̂��ߕ�Ԕ䗦�����Z�b�g����
		m_t = 0.0f;
		// ���̃R�}���h�̂��߃R�}���h�C���f�b�N�X���C���N�������g����
		m_commandIndex++;
	}
	// �}�N���C���f�b�N�X���}�N���R�}���h���Ɠ����ɂȂ�����}�N���R�}���h���I������
	if (m_commandIndex == m_macroCommand.size())
	{
		// �}�N���R�}���h�C���f�b�N�X�����Z�b�g����
		m_commandIndex = 0;
		// �R�}���h���s���I������
		Messenger::SetCommandExecution(false);
		// �R�}���_�[���I������
		return false;
	}
	return true;
}
