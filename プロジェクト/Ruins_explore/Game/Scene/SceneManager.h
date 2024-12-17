/*
	@file	SceneManager.h
	@brief	シーンマネージャクラス
*/
#pragma once
#include "Game/Interface/IScene.h"

class SceneManager
{
public:
	// コンストラクタ
	SceneManager();
	// デストラクタ
	~SceneManager();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(float elapsedTime);
	// 描画する
	void Render();
	// 終了処理
	void Finalize();

private:
	// シーンを変更する
	void ChangeScene(IScene::SceneID sceneID);
	// シーンを作成する
	void CreateScene(IScene::SceneID sceneID);
	// シーンを削除する
	void DeleteScene();

private:
	std::unique_ptr<IScene> m_currentScene;
};
