#pragma once
#ifndef COMMANDER_DEFINED
#define COMMANDER_DEFINED
#include "ICommand.h"

// Commander�N���X���`����
class Commander
{
public:
	// �R�}���h���擾����
	ICommand* GetCommand() { return m_command; }
	// �R�}���h��ݒ肷��
	void SetCommand(ICommand* command) { m_command = command; }
	// �p�����[�^���擾����
	Parameter GetParameter() { return m_parameter; }
	// �p�����[�^��ݒ肷��
	void SetParameter(const Parameter& parameter) { m_parameter = parameter; }

	// �}�N���R�}���h�����擾����
	size_t GetMacroCommandNumber() { return m_macroCommand.size(); }

public:
	// �R���X�g���N�^
	Commander();
	// �f�X�g���N�^
	~Commander();
	// ����������
	void Initialize();
	// �}�N���R�}���h���N���A����
	void ClearCommand();
	// �}�N���R�}���h�ɃR�}���h��ǉ�����
	void AddCommand(std::unique_ptr<ICommand> command);
	// �}�N���R�}���h�����s����
	bool ExecuteMacroCommand(DirectX::SimpleMath::Vector3& position, DirectX::SimpleMath::Quaternion& angle);
	// ���`��Ԃ����Z�b�g����
	void ResetLerp() { m_t = 0.0f; }

private:
	// �R�}���h
	ICommand* m_command;
	// �}�N���R�}���h�z��
	std::vector<std::unique_ptr<ICommand>> m_macroCommand;
	// �p�����[�^
	Parameter m_parameter;
	// �}�N���p�����[�^�z��
	std::vector<Parameter> m_macroParameter;
	// ��Ԕ䗦
	float m_t;
	// �R�}���h�C���f�b�N�X
	int m_commandIndex;
};

#endif		// COMMANDER_DEFINED

