/*
	@file	TitleScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "TitleScene.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_isChangeScene{},
	m_titleSceneUI{}
{
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

	// タイトルUI管理クラスを作成する
	m_titleSceneUI = std::make_unique<TitleSceneUI>(this);
	// 初期化する
	m_titleSceneUI->Initialize();
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
// 後始末する
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
		return IScene::SceneID::PLAY;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}

void TitleScene::ChangeScene()
{
	m_isChangeScene = true;
}
