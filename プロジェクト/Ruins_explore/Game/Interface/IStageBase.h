/*
	@file	IStageBase.h
	@brief	ステージのインターフェース
*/
#pragma once

class IStageBase
{
public:
	virtual ~IStageBase() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update() = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};
