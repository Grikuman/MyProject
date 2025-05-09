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
	// ステージをクリアしたかどうか
	bool IsEndStage() const override { return m_isEndStage; }

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
	// BGMの音量
	const float BGM_VOLUME = 0.05f;
	// 移動の範囲制限
	const float COLLISION_DISTANCE = 20.0f;
	// ミッション1の必要移動量
	const int MISSION_MOVE_CNT = 120;
	// ミッション3の必要攻撃量
	const float MISSION_ATTACK_CNT = 200;

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
	// ステージ終了フラグ
	bool m_isEndStage;
	// 移動カウント
	int m_moveCnt;
};
