/*
	ファイル名：TunomaruDown.cpp
	　　　概要：つのまるのダウン状態を管理するクラス
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruDown.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruDown::TunomaruDown(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
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
	m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruDown::Update()
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

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruDown::Finalize()
{
    
}
