/*
	@file	Stage1-1.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"

#include "Game/StageObject/Sky.h"
#include "Game/StageObject/Field.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/UI/TimeUI.h"


namespace NRLib
{
	class FixedCamera;
};

class Stage1_2 final : public IStage
{
public:
	// 次のステージIDを取得する
	StageID GetNextStageID() const override { return StageID::NONE; }
	// ステージをクリアしたかどうか
	bool IsClearStage() const override { return m_isClearStage; }
public:
	// コンストラクタ
	Stage1_2();
	// コンストラクタ
	~Stage1_2() override;
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
	// プレイヤー
	std::unique_ptr<Player> m_player;
	// 天球
	std::unique_ptr<Sky> m_sky;
	// フィールド
	std::unique_ptr<Field> m_field;
	// エネミースポナー
	std::unique_ptr<EnemySpawner> m_enemySpawner;
	//TextUI
	std::unique_ptr<TimeUI> m_timeUI;
	// プレイシーンUI

	// ステージクリアフラグ
	bool m_isClearStage;
	// ゲーム時間
	float m_gameTime;
};
