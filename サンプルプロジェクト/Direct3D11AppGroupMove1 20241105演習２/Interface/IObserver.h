#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED
#include "Interface/ISubject.h"

class ISubject;

// IObserverインターフェースを定義する
class IObserver
{
public:
	// キーが押下げられたら時に呼び出される
	virtual void OnKeyPressed(const DirectX::Keyboard::Keys& key) = 0;
};

#endif	// IOBSERVER_DEFINED
