#include "Framework/pch.h"
#include "Command/Header/FloatCommand.h"

// �R���X�g���N�^
FloatCommand::FloatCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// ���`��Ԃ��v�Z����
DirectX::SimpleMath::Vector3 FloatCommand::Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// ����R�}���h�����s����
void FloatCommand::Execute(Parameter& parameter, const float& t)
{
	// ���`��Ԃŕ��㒆�̌��݈ʒu���v�Z����
	parameter.SetCurrentPosition(Lerp(parameter.GetStartPosition(), parameter.GetEndPosition(), t));
	// �p�����[�^���X�V����
	m_parameter = parameter;
}