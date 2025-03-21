/*
	ファイル名：SceneManager.cpp
	　　　概要：シーン全体を管理するクラス
*/
#include "pch.h"
#include "SceneManager.h"
//---------------------------
#include "PlayScene.h"
#include "TitleScene.h"
#include "QuestSelectScene.h"
#include "ResultScene.h"
//---------------------------
#include "Game/Screen.h"
#include"Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/InputDevice.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <iostream>


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_fade{}
{
	// フェードを作成する
	m_fade = std::make_unique<Fade>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
SceneManager::~SceneManager()
{
	Finalize();
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void SceneManager::Initialize()
{
	// 初期シーンを設定
	ChangeScene(IScene::SceneID::TITLE);
	// フェードを初期化する
	m_fade->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	// シーンを更新する
	m_currentScene->Update(elapsedTime);
	// フェードを更新する
	m_fade->Update();
	// 説明用変数：次のシーン
	const IScene::SceneID nextSceneID = m_currentScene->GetNextSceneID();
	// シーンを変更しないとき
	if (nextSceneID == IScene::SceneID::NONE) return;
	// シーンを変更するとき
	ChangeScene(nextSceneID);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void SceneManager::Render()
{
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::Identity;

	// シーンを描画する
	m_currentScene->Render();
	// フェードを描画する
	m_fade->Render(view, proj);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void SceneManager::Finalize()
{
	DeleteScene();
	m_fade->Finalize();
}

//---------------------------------------------------------
// シーンを変更する
//---------------------------------------------------------
void SceneManager::ChangeScene(IScene::SceneID sceneID)
{
	m_fade->FadeIn();
	DeleteScene();
	m_fade->FadeOut();
	CreateScene(sceneID);
}

//---------------------------------------------------------
// シーンを作成する
//---------------------------------------------------------
void SceneManager::CreateScene(IScene::SceneID sceneID)
{
	assert(m_currentScene == nullptr);

	switch (sceneID)
	{
		case IScene::SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>();
			break;
		case IScene::SceneID::MAPSELECT:
			m_currentScene = std::make_unique<QuestSelectScene>();
			break;
		case IScene::SceneID::PLAY:
			m_currentScene = std::make_unique<PlayScene>();
			break;
		case IScene::SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::シーン名が存在しません！");
	}

	assert(m_currentScene && "SceneManager::CreateScene::次のシーンが生成されませんでした！");
	m_currentScene->Initialize();
}

//---------------------------------------------------------
// シーンを削除する
//---------------------------------------------------------
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}
