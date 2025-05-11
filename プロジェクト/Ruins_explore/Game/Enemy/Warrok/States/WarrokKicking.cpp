/*
	ファイル名：WarrokKicking.cpp
	　　　概要：ウォーロックのキック状態を管理するクラス
*/
#include "pch.h"
#include "WarrokKicking.h"
#include "Game/Enemy/Warrok/Warrok.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
WarrokKicking::WarrokKicking(Warrok* warrok)
	:
    m_warrok(warrok)
{
	// アニメーションを作成する
	m_animation = std::make_unique<WarrokKickingAnimation>(warrok);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
WarrokKicking::~WarrokKicking()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void WarrokKicking::Initialize()
{
	// アニメーションを初期化する
	m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void WarrokKicking::Update()
{
	// 斬りつけの処理
	Kicking();
	// 歩き状態への移行処理
	TransitionToWalking();
	
	// アニメーションを更新する
	m_animation->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void WarrokKicking::Render()
{
	// アニメーションを描画する
	m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void WarrokKicking::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// キックの処理
//---------------------------------------------------------
void WarrokKicking::Kicking()
{
	
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void WarrokKicking::TransitionToWalking()
{
	// アニメーションが終了したら待機状態へ移行する
	if (m_animation->IsEndAnimation())
	{
		m_warrok->ChangeState(m_warrok->GetWarrokWalking());
	}
}