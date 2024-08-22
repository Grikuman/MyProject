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
#include "Libraries/NRLib/FixedCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_commonResources{},
	m_isChangeScene{}
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
void TitleScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	// シーン変更フラグを初期化する
	m_isChangeScene = false;

	// スプライトバッチとスプライトフォントを初期化
	spriteBatch = std::make_unique<SpriteBatch>(m_commonResources->GetDeviceResources()->GetD3DDeviceContext());
	spriteFont = std::make_unique<SpriteFont>(
		m_commonResources->GetDeviceResources()->GetD3DDevice(), 
		L"Resources/Fonts/SegoeUI_18.spritefont");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	auto& kb = m_commonResources->GetInputManager()->GetKeyboardTracker();
	if (kb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleScene::Render()
{
	spriteBatch->Begin();

	// 数値を文字列に変換
	std::wstring timeString = L"Space to Start";

	// 表示するテキスト、位置、色を指定して描画
	spriteFont->DrawString(spriteBatch.get(), timeString.c_str(),
		SimpleMath::Vector2(width / 2, height / 2), // position
		Colors::White,                        // color
		0.f,                                  // rotate
		SimpleMath::Vector2::Zero,
		3.f                                   // scale
	);

	spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleScene::Finalize()
{

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
