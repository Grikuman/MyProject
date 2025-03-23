#pragma once
#ifndef ROTETE_COMMAND_DEFINED
#define ROTETE_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// ��]�R�}���h
class RotateCommand : public ICommand
{
public:
	// �R�}���hID���擾����
	CommandID GetCommandID() { return CommandID::ROTATE; }
	// �p�����[�^���擾����
	Parameter& GetParameter() { return m_parameter; }
	// �p�����[�^��ݒ肷��
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// �R���X�g���N�^
	RotateCommand(const Parameter& parameter);
	// ��]�R�}���h�����s����
	void Execute(Parameter& parameter, const float& t);

private:
	// �p�����[�^
	Parameter m_parameter;
};

#endif		// ROTATE_COMMAND_DEFINED