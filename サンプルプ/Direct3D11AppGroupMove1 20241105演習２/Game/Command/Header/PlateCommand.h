#pragma once
#pragma once
#ifndef PLATE_COMMAND_DEFINED
#define PLATE_COMMAND_DEFINED
#include "Interface/ICommand.h"
#include "Command/Header/Parameter.h"

// �v���[�g���J����
class PlateCommand : public ICommand
{
	enum State : int { MOVE, STOP };

public:
	// �R�}���hID���擾����
	CommandID GetCommandID() { return CommandID::PLATE; }
	// �p�����[�^���擾����
	Parameter& GetParameter() { return m_parameter; }
	// �p�����[�^��ݒ肷��
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

public:
	// �R���X�g���N�^
	PlateCommand(const Parameter& parameter);
	// ���`��Ԃ��v�Z����
	DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t);
	// �ړ��R�}���h�����s����
	void Execute(Parameter& parameter, const float& t);

private:
	// �p�����[�^
	Parameter m_parameter;
};

#endif		// PLATE_COMMAND_DEFINED
