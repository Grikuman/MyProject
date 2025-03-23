#pragma once
#ifndef ISUBJECT_DEFINED
#define ISUBJECT_DEFINED
#include "IComponent.h"

class IComponent;

// ISubject�C���^�[�t�F�[�X���`����
class ISubject
{
public:
	// �f�X�g���N�^
	virtual ~ISubject() = default;
	// �ώ@�҂��A�^�b�`����
	virtual void Attach(const DirectX::Keyboard::Keys& key, IComponent* observer) = 0;
	// �ώ@�҂��f�^�b�`����
	virtual void Detach(const DirectX::Keyboard::Keys& key, IComponent* component) = 0;
	// �ʒm����
	virtual void Notify(const DirectX::Keyboard::State& keyboardState) = 0;
};

#endif	// ISUBJECT_DEFINED

