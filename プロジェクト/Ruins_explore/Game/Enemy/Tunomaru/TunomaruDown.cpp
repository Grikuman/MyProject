/*
	ファイル名：TunomaruDown.cpp
	　　　概要：つのまるのダウン状態を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruDown.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruDown::TunomaruDown(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_downTime{},
	m_effect{}
{
	// エフェクトを作成する
	m_effect = std::make_unique<DownEffect>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruDown::~TunomaruDown()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruDown::Initialize()
{
	// エフェクトを初期化する
	m_effect->Initialize(m_tunomaru->GetPosition());
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruDown::Update()
{
	// ダウン処理
	Down();
	// エフェクトを更新する
	m_effect->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruDown::Render()
{
	// エフェクトを描画する
	m_effect->Render(m_tunomaru->GetPosition());
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruDown::Finalize()
{
	m_effect->Finalize();
}

//---------------------------------------------------------
// ダウン処理
//---------------------------------------------------------
void TunomaruDown::Down()
{
	// ダウン時間を減少させる
	m_downTime--;
	// ダウン時間が終了した場合
	if (m_downTime <= 0.f)
	{
		// ダウン時間をリセットする
		m_downTime = MAX_DOWNTIME;
		// サーチ状態へ移行する
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruSearch());
	}
}
