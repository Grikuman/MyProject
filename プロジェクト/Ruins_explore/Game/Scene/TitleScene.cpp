/*
	ファイル名：TitleScene.cpp
	　　　概要：タイトルシーンを管理するクラス
*/
#include "pch.h"
#include "TitleScene.h"
#include "Framework/DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Framework/Graphics.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_isChangeScene{},
	m_titleSceneUI{}
{
	// タイトルUI管理クラスを作成する
	m_titleSceneUI = std::make_unique<TitleSceneUI>(this);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TitleScene::~TitleScene()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TitleScene::Initialize()
{
	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	// 初期化する
	m_titleSceneUI->Initialize();
	// BGMを再生
	Audio::GetInstance()->PlayBGM("TitleBGM",0.05f);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// タイトルUI管理クラスを更新する
	m_titleSceneUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleScene::Render()
{
	m_titleSceneUI->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void TitleScene::Finalize()
{
	m_titleSceneUI->Finalize();
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::MAPSELECT;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}

//---------------------------------------------------------
// シーン遷移する
//---------------------------------------------------------
void TitleScene::ChangeScene()
{
	m_isChangeScene = true;
}
