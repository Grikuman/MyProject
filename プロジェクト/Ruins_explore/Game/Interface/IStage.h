/*
	ファイル名：IStage.h
	　　　概要：ステージのインターフェース
*/
#pragma once

// ステージID
enum class StageID
{
	NONE,
	TutorialStage,
	Stage1,
};

class IStage
{
public:
	// ステージが終了したかどうか
	virtual bool IsEndStage() const = 0;

public:
	virtual ~IStage() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(float elapsedTime) = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};
