#pragma once
#ifndef ICOMMAND_DEFINED
#define ICOMMAND_DEFINED
#include "Command/Header/Parameter.h"

// ICommand�C���^�[�t�F�[�X���`����
class ICommand
{
public:
	// �R�}���hID
	enum CommandID : int { MOVE, FLOAT, ROTATE, PLATE, SHOOT, UP, DOWN};

public:
	virtual CommandID GetCommandID() = 0;
	// �p�����[�^���擾����
	virtual Parameter& GetParameter() = 0;
	// �p�����[�^��ݒ肷��
	virtual void SetParameter(const Parameter& parameter) = 0;
	// ���s����
	virtual void Execute(Parameter& parameter, const float& t) = 0;
	// ���z�f�X�g���N�^
	virtual ~ICommand() = default;
};

#endif	// ICOMMAND_DEFINED



