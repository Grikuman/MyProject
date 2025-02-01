/*
	ファイル名：NeedleBossDown.cpp
	　　　概要：岩ボスのダウン状態を管理するクラス
*/
#include "pch.h"
#include "NeedleBoss.h"
#include "NeedleBossDown.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
NeedleBossDown::NeedleBossDown(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{}
{
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
NeedleBossDown::~NeedleBossDown()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void NeedleBossDown::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void NeedleBossDown::Update()
{
	// ダウン時間を減少させる
	m_downTime--;
	// ダウン時間が終了した場合
	if (m_downTime <= 0.f)
	{
		// ダウン時間をリセットする
		m_downTime = MAX_DOWNTIME;
		// サーチ状態へ移行する
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossSearch());
	}
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void NeedleBossDown::Finalize()
{
    
}
