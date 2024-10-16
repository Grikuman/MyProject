/*
	@file	MapSelectScene.h
	@brief	マップセレクトシーンクラス
*/
#pragma once
#include "IScene.h"

class MapSelectUI;

class MapSelectScene final : public IScene
{
public:
	MapSelectScene();
	~MapSelectScene() override;

	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime)override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;
	// シーン遷移する
	void ChangeScene();

private:
	// シーンチェンジフラグ
	bool m_isChangeScene;

	// マップセレクトUI
	std::unique_ptr<MapSelectUI> m_mapSelectUI;
};
