#include "Framework/pch.h"
#include "Command/Header/RotateCommand.h"

// �R���X�g���N�^
RotateCommand::RotateCommand(const Parameter& parameter)
	:
	m_parameter(parameter)
{
}

// ��]�R�}���h�����s����
void RotateCommand::Execute(Parameter& parameter, const float& t)
{
	// �N�H�[�^�j�I���̐��`��Ԃ��s��
	parameter.SetCurrentAngle(DirectX::SimpleMath::Quaternion::Lerp(parameter.GetStartAngle(), parameter.GetEndAngle(), t));
	// �p�����[�^���X�V����
	m_parameter = parameter;
}