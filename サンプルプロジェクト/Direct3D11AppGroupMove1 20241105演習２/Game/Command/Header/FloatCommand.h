#pragma once
#ifndef FLOAT_COMMAND_DEFINED
#define FLOAT_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// ����R�}���h
class FloatCommand : public ICommand
{
public:
	// �R�}���hID���擾����
	CommandID GetCommandID() { return CommandID::FLOAT; }
	// �p�����[�^���擾����
	Parameter& GetParameter() { return m_parameter; }
	// �p�����[�^��ݒ肷��
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// �R���X�g���N�^
	FloatCommand(const Parameter& parameter);
	// ���`��Ԃ��v�Z����
	DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t);
	// ����R�}���h�����s����
	void Execute(Parameter& parameter, const float& t);

private:
	// �p�����[�^
	Parameter m_parameter;
};

#endif		// FLOAT_COMMAND_DEFINED
