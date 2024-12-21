/*
	ファイル名：IStage.h
	　　　概要：ステージのインターフェース
*/
#pragma once

// ステージID
enum class StageID
{
	NONE,
	Stage1_1,
	Stage1_2,
};

class IStage
{
public:
	// 次のステージIDを取得する
	virtual StageID GetNextStageID() const = 0;
	// ステージをクリアしたかどうか
	virtual bool IsClearStage() const = 0;

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
