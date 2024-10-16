/*
	@file	ResultScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "ResultScene.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ResultScene::~ResultScene()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ResultScene::Initialize()
{
	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	// リザルトシーンUI
	m_resultSceneUI = std::make_unique<ResultSceneUI>(this);
	m_resultSceneUI->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();
	if (kb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}

	m_resultSceneUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::Render()
{
	m_resultSceneUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultScene::Finalize()
{

}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}

void ResultScene::ChangeScene()
{
	m_isChangeScene = true;
}
