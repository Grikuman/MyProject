/*
	ファイル名：ResultScene.cpp
	　　　概要：リザルトシーンを管理するクラス
*/
#include "pch.h"
#include "ResultScene.h"
#include "Framework/DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Framework/Graphics.h"
#include "Game/Camera/FixedCamera.h"
#include "Framework/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_isChangeScene{},
	m_resultSceneUI{}
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

	// UIを作成する
	m_resultSceneUI = std::make_unique<ResultSceneUI>(this);
	// UIを初期化する
	m_resultSceneUI->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードを取得する
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();

	// スペースキーを押したらシーン遷移
	if (kb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}
	// UIを更新する
	m_resultSceneUI->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::Render()
{
	// UIを描画する
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
