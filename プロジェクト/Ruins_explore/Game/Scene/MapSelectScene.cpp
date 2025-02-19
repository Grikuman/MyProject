/*
	ファイル名：MapSelectScene.cpp
	　　　概要：マップセレクトシーンを管理するクラス
*/
#include "pch.h"
#include "MapSelectScene.h"
#include "Game/UI/MapSelectUI.h"
#include "Framework/DeviceResources.h"

#include <cassert>
#include "Framework/Graphics.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MapSelectScene::MapSelectScene()
	:
	m_isChangeScene{},
	m_mapSelectUI{}
{
	// UIを作成する
	m_mapSelectUI = std::make_unique<MapSelectUI>(this);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MapSelectScene::~MapSelectScene()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MapSelectScene::Initialize()
{
	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	// UIを初期化する
	m_mapSelectUI->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MapSelectScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// UIを更新する
	m_mapSelectUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MapSelectScene::Render()
{
	// UIを描画する
	m_mapSelectUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MapSelectScene::Finalize()
{
	// UIの終了処理
	m_mapSelectUI->Finalize();
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID MapSelectScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}
	// シーン変更がない場合
	return IScene::SceneID::NONE;
}

//---------------------------------------------------------
// シーンを変更する
//---------------------------------------------------------
void MapSelectScene::ChangeScene()
{
	m_isChangeScene = true;
}
