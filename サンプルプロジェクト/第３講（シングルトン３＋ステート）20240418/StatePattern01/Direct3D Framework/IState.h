#pragma once
#ifndef STATE_DEFINED
#define STATE_DEFINED
#include "StepTimer.h"

// IState�C���^�[�t�F�C�X���`���� 
class IState
{
public:
	// ���������� 
	virtual void Initialize() = 0;
	// ���������s����
	virtual void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) = 0;
	// �e�N�X�`����`�悷��
	virtual void Render() = 0;
	// ��n��������
	virtual void Finalize() = 0;
	// ���z�f�X�g���N�^
	virtual ~IState() = default;
};

#endif // STATE_DEFINED
