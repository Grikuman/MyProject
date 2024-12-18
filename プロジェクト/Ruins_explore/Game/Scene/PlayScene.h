/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Interface/IStage.h"
#include "Game/Stage/StageFactory.h"


namespace NRLib
{
	class FixedCamera;
};

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
	void Update(float elapsedTime)override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// 次のステージへの移行を処理する
	void TransitionToNextStage();

private:
	// 現在のステージ
	std::unique_ptr<IStage> m_currentStage;
	// シーンチェンジフラグ
	bool m_isChangeScene;
	
};
