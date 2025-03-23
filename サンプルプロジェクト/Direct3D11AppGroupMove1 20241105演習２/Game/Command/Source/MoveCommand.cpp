#include "Framework/pch.h"
#include "Command/Header/MoveCommand.h"

// �R���X�g���N�^
MoveCommand::MoveCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// ���`��Ԃ��v�Z����
DirectX::SimpleMath::Vector3 MoveCommand::Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// �ړ��R�}���h�����s����
void MoveCommand::Execute(Parameter& parameter, const float& t)
{
	// ���`��Ԃňړ����̌��݈ʒu���v�Z����
	parameter.SetCurrentPosition(Lerp(parameter.GetStartPosition(), parameter.GetEndPosition(), t));
	// �p�����[�^���X�V����
	m_parameter = parameter;
}
