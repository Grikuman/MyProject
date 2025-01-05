/*
	ファイル名：Stage1_1.h
	　　　概要：ステージ1_1を管理するクラス
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"

#include "Game/StageObject/Sky.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"
#include "Game/Stage/StageObject.h"

namespace NRLib
{
	class FixedCamera;
};

class Stage1_1 final : public IStage
{
public:
	// 次のステージIDを取得する
	StageID GetNextStageID() const override { return StageID::Stage1_2; }
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
	// ゲームの制限時間
	static const int MAX_GAMETIME = 60;

private:
	// エネミー
	std::unique_ptr<StageEnemy> m_stageEnemy;
	// ステージのオブジェクト
	std::unique_ptr<StageObject> m_stageObject;
	// ステージの名前
	std::string m_stageName;
	// プレイヤー
	std::unique_ptr<Player> m_player;
	// 天球
	std::unique_ptr<Sky> m_sky;
	//TextUI
	std::unique_ptr<TimeUI> m_timeUI;
	// プレイシーンUI

	// ステージクリアフラグ
	bool m_isClearStage;
	// ゲーム時間
	float m_gameTime;
};
