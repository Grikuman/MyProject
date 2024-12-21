/*
	ファイル名：MapSelectScene.h
	　　　概要：マップセレクトシーンを管理するクラス
*/
#pragma once
#include "Game/Interface/IScene.h"

class MapSelectUI;

class MapSelectScene final : public IScene
{
public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

public:
	// シーンを変更する
	void ChangeScene();

public:
	// コンストラクタ
	MapSelectScene();
	// デストラクタ
	~MapSelectScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// マップセレクトUI
	std::unique_ptr<MapSelectUI> m_mapSelectUI;
	// シーンチェンジフラグ
	bool m_isChangeScene;
};
