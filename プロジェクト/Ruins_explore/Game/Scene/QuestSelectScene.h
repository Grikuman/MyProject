/*
	ファイル名：QuestSelectScene.h
	　　　概要：クエスト選択シーンを管理するクラス
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Transition/StageStart.h"

class QuestSelectUI;

class QuestSelectScene final : public IScene
{
public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

public:
	// シーンを変更する
	void ChangeScene();

public:
	// コンストラクタ
	QuestSelectScene();
	// デストラクタ
	~QuestSelectScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// クエスト選択のUI
	std::unique_ptr<QuestSelectUI> m_questSelectUI;
	// クエスト開始の演出
	std::unique_ptr<StageStart> m_stageStart;
	// シーンチェンジフラグ
	bool m_isChangeScene;
};
