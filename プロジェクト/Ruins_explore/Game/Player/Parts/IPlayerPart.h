/*
	@file	IState.h
	@brief	ステートのインターフェース
*/
#pragma once

class IPlayerPart
{
public:
	virtual ~IPlayerPart() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update() = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};
