/*
	ファイル名：Stage1_1.h
	　　　概要：ステージ1_1を管理するクラス
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"
#include "Game/Stage/StageCollision.h"
#include "Game/Stage/StageDecoration.h"

class Stage1_1 final : public IStage
{
public:
	// 次のステージIDを取得する
	StageID GetNextStageID() const override { return StageID::NONE; }
	// ステージをクリアしたかどうか
	bool IsClearStage() const override { return m_isClearStage; }

public:
	// コンストラクタ
	Stage1_1(std::string stageName);
	// コンストラクタ
	~Stage1_1() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// ステージの遷移処理
	void Transition();

private:
	// ゲームの制限時間
	static const int MAX_GAMETIME = 60;

private:
	// ステージの敵
	std::unique_ptr<StageEnemy> m_stageEnemy;
	// ステージの衝突判定
	std::unique_ptr<StageCollision> m_stageCollision;
	// ステージの装飾オブジェクト
	std::unique_ptr<StageDecoration> m_stageDecoration;
	// プレイヤー
	std::unique_ptr<Player> m_player;
	//時間UI
	std::unique_ptr<TimeUI> m_timeUI;
	// ステージの名前
	std::string m_stageName;
	// ステージクリアフラグ
	bool m_isClearStage;
	// ゲーム時間
	float m_gameTime;
};
