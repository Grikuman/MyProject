/*
	ファイル名：PlayScene.h
	　　　概要：プレイシーンを管理するクラス
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Interface/IStage.h"
#include "Game/Transition/StageEnd.h"

class PlayScene final : public IScene
{
public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

public:
	// コンストラクタ
	PlayScene();
	// コンストラクタ
	~PlayScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// ステージの初期化
	void StageInitialize();

private:
	// 現在のステージ
	std::unique_ptr<IStage> m_currentStage;
	// シーンチェンジフラグ
	bool m_isChangeScene;
	// ステージ終了演出
	std::unique_ptr<StageEnd> m_stageEnd;
};
