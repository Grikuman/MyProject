/*
	@file	MapSelectScene.cpp
	@brief	マップセレクトシーンクラス
*/
#include "pch.h"
#include "MapSelectScene.h"
#include "Game/UI/MapSelectUI.h"
#include "WorkTool/DeviceResources.h"

#include <cassert>
#include "WorkTool/Graphics.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MapSelectScene::MapSelectScene()
	:
	m_isChangeScene{},
	m_mapSelectUI{}
{
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

	// タイトルUI管理クラスを作成する
	m_mapSelectUI = std::make_unique<MapSelectUI>(this);
	// 初期化する
	m_mapSelectUI->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MapSelectScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// タイトルUI管理クラスを更新する
	m_mapSelectUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MapSelectScene::Render()
{
	m_mapSelectUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MapSelectScene::Finalize()
{
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

void MapSelectScene::ChangeScene()
{
	m_isChangeScene = true;
}
