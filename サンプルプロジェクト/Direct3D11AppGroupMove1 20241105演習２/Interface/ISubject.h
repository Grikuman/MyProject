#pragma once
#ifndef ISUBJECT_DEFINED
#define ISUBJECT_DEFINED
#include "IComponent.h"

class IComponent;

// ISubjectインターフェースを定義する
class ISubject
{
public:
	// デストラクタ
	virtual ~ISubject() = default;
	// 観察者をアタッチする
	virtual void Attach(const DirectX::Keyboard::Keys& key, IComponent* observer) = 0;
	// 観察者をデタッチする
	virtual void Detach(const DirectX::Keyboard::Keys& key, IComponent* component) = 0;
	// 通知する
	virtual void Notify(const DirectX::Keyboard::State& keyboardState) = 0;
};

#endif	// ISUBJECT_DEFINED

