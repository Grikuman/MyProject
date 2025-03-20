/*
	ファイル名：TutorialStage.h
	　　　概要：ステージ1_1を管理するクラス
*/
#pragma once
#include "Game/Interface/IStage.h"
#include "Game/Player/Player.h"
#include "Game/UI/TimeUI.h"
#include "Game/Stage/StageEnemy.h"
#include "Game/Stage/StageCollision.h"
#include "Game/Stage/StageDecoration.h"
#include "Game/UI/TutorialGuideUI.h"
#include "Game/Enemy/PracticeEnemy/PracticeEnemy.h"

class TutorialStage final : public IStage
{
public:
	// 次のステージIDを取得する
	StageID GetNextStageID() const override { return StageID::NONE; }
	// ステージをクリアしたかどうか
	bool IsClearStage() const override { return m_isClearStage; }

public:
	// コンストラクタ
	TutorialStage(std::string stageName);
	// コンストラクタ
	~TutorialStage() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 衝突判定
	void Collision();
	// ステージの遷移処理
	void Transition();
	// チュートリアルのミッション処理
	void Mission();

private:
	// プレイヤー
	std::unique_ptr<Player> m_player;
	// チュートリアルガイドのUI
	std::unique_ptr<TutorialGuideUI> m_tutorialGuideUI;
	// チュートリアル用の敵
	std::unique_ptr<PracticeEnemy> m_practiceEnemy;
	// ステージのモデル
	DirectX::Model* m_stageModel;
	// ステージの名前
	std::string m_stageName;
	// ステージクリアフラグ
	bool m_isClearStage;
	// 移動カウント
	int m_moveCnt;
};
