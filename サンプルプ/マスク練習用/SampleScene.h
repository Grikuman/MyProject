//--------------------------------------------------------------------------------------
//	File: SampleScene.h
//
//	シーンの雛型に使用してください
//
//	Date: 2023.3.25
//	Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once
#include "ImaseLib/SceneManager.h"
#include "ImaseLib/TaskManager.h"
#include "UserResources.h"
#include "SampleTask.h"

class SampleScene : public Imase::Scene<UserResources>
{
private:

	//	タスクマネージャー
	Imase::TaskManager m_taskManager;

	//	サンプルタスクへのポインタ
	SampleTask* m_sampleTask;

public:

	//	コンストラクタ
	SampleScene();

	//	初期化
	void Initialize() override;

	//	更新
	void Update(float elapsedTime) override;

	//	描画
	void Render() override;

	//	終了処理
	void Finalize() override;

	//	デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	//	ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	//	デバイスロストした時に呼び出される関数
	void OnDeviceLost() override;

};

